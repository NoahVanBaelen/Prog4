#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl2.h"
#include "imgui_plot.h"
#include <iostream>
#include <fstream>

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();

	//hint: something should come here
	//EX01
	/*ImGui::Begin("Excercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	static float y_dataPlot1[11];
	static float x_data[11] = { 1.f,2.f,4.f,8.f,16.f,32.f,64.f,128.f,256.f,512.f,1024.f };

	static int numSamplesEX01{ 10 };
	ImGui::InputInt("# samples", &numSamplesEX01);

	static bool clickEX1{ false };
	if (ImGui::Button("Trash the cache"))
	{
		clickEX1 = true; 
		std::string path{ "..\\Data\\W4_programs\\EX01.exe " + std::to_string(numSamplesEX01) + " EX01Result.txt"};
		int returnCode = std::system(path.c_str());
		if (returnCode == 0) 
		{
			std::ifstream fileToRead;
			std::string line;
			int index{ 0 };
			fileToRead.open("EX01Result.txt");

			while (std::getline(fileToRead, line))
			{
				y_dataPlot1[index] = static_cast<float>(std::stoll(line))/1000.f;
				index++;
			}
			fileToRead.close();
		}
	}

	if (clickEX1)
	{
		ImGui::PlotConfig conf;

		conf.values.xs = x_data;
		conf.values.ys = y_dataPlot1;
		conf.values.color = ImColor(255, 0, 0);
		conf.values.count = 11;
		conf.scale.min = y_dataPlot1[10];
		conf.scale.max = y_dataPlot1[0];
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 3;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 1;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plotEX01", conf);
	}
	ImGui::End();*/

	//EX02
	/*ImGui::Begin("Excercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	static float y_dataPlot2[11];
	static float y_dataPlot2Alt[11];

	static int numSamplesEX02{ 10 };
	ImGui::InputInt("# samples", &numSamplesEX02);

	static bool clickEX2{ false };
	if (ImGui::Button("Trash the cache with GameObject3D"))
	{
		clickEX2 = true;
		std::string path{ "..\\Data\\W4_programs\\EX02.exe " + std::to_string(numSamplesEX02) + " EX02Result.txt" };
		int returnCode = std::system(path.c_str());
		if (returnCode == 0)
		{
			std::ifstream fileToRead;
			std::string line;
			int index{ 0 };
			fileToRead.open("EX02Result.txt");

			while (std::getline(fileToRead, line))
			{
				y_dataPlot2[index] = static_cast<float>(std::stoll(line)) / 1000.f;
				index++;
			}
			fileToRead.close();
		}
	}

	if (clickEX2)
	{
		ImGui::PlotConfig conf;

		conf.values.xs = x_data;
		conf.values.ys = y_dataPlot2;
		conf.values.color = ImColor(255, 0, 0);
		conf.values.count = 11;
		conf.scale.min = y_dataPlot2[10];
		conf.scale.max = y_dataPlot2[0];
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 3;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 1;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plotEX02", conf);
	}

	static bool clickEX2Alt{ false };
	if (ImGui::Button("Trash the cache with GameObject3DAlt"))
	{
		clickEX2Alt = true;
		std::string path{ "..\\Data\\W4_programs\\EX02_Alt.exe " + std::to_string(numSamplesEX02) + " EX02AltResult.txt" };
		int returnCode = std::system(path.c_str());
		if (returnCode == 0)
		{
			std::ifstream fileToRead;
			std::string line;
			int index{ 0 };
			fileToRead.open("EX02AltResult.txt");

			while (std::getline(fileToRead, line))
			{
				y_dataPlot2Alt[index] = static_cast<float>(std::stoll(line)) / 1000.f;
				index++;
			}
			fileToRead.close();
		}
	}

	if (clickEX2Alt)
	{
		ImGui::PlotConfig conf;

		conf.values.xs = x_data;
		conf.values.ys = y_dataPlot2Alt;
		conf.values.color = ImColor(0, 255, 0);
		conf.values.count = 11;
		conf.scale.min = y_dataPlot2Alt[10];
		conf.scale.max = y_dataPlot2Alt[0];
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 3;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 1;
		conf.frame_size = ImVec2(250, 100);
		conf.line_thickness = 2.f;

		ImGui::Plot("plotEX02Alt", conf);
	}

	if (clickEX2 && clickEX2Alt)
	{
		ImGui::Text("Combined:", IMGUI_VERSION, IMGUI_VERSION_NUM);

		static const float* y_dataCombine[2] = { y_dataPlot2, y_dataPlot2Alt };
		static ImU32 colors[2] = { ImColor(255, 0, 0), ImColor(0, 255, 0) };
		ImGui::PlotConfig conf;
		float min = y_dataPlot2[10];
		float max = y_dataPlot2[0];
		
		if (y_dataPlot2[10] > y_dataPlot2Alt[10])
		{
			min = y_dataPlot2Alt[10];
		}

		if (y_dataPlot2[0] < y_dataPlot2Alt[0])
		{
			max = y_dataPlot2Alt[0];
		}

		conf.values.count = 11;
		conf.values.xs = x_data;
		conf.values.ys_list = y_dataCombine;
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.scale.min = min;
		conf.scale.max = max;
		conf.grid_x.show = true;
		conf.grid_y.show = true;
		conf.tooltip.show = true;
		conf.grid_x.size = 128;
		conf.grid_x.subticks = 3;
		conf.grid_y.size = 0.5f;
		conf.grid_y.subticks = 1;
		conf.frame_size = ImVec2(250, 100);
		conf.selection.start = 0;
		conf.selection.length = 0;
		conf.line_thickness = 2.f;

		ImGui::Plot("plotEX02Combine", conf);
	}
	ImGui::End();*/

	if (m_showDemo)
	{
		bool show = m_showDemo;
		ImGui::ShowDemoWindow(&show);
	}
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
