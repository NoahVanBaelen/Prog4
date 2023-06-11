source control: https://github.com/NoahVanBaelen/Prog4

About the engine:

Ik denk dat mijn engine in het algemeen basic is maar als ik toch een paar higlights moet geven

-De Collision Handling: Ik heb een zelf gemaakte classe voor collision deze classe heeft een vector vol met collisionBox objects
deze houden bij de positie the groote van de box, of hem static is
en een ID dat zegt bij welke group hij behourdt en een vector van IDs voor welke groupen hij kan mee colliden op deze manier can somige gameObjecten colliden met elkaar en andere niet, dit wordt ook nog gebruikt voor triggers en een 2D rayCast.

-De GameState: de gamestate houdt bij welke scene actieve is en zo wordt alleen die scene geupdated de GameState zorgt ook voor welke welke commands/controls momenteel actieve zijn

-Het Hergebruik van gameobjecten in meerdere scenes: Door het gebruik van de bevoormelde GameState system samen met een goed gebruik van observers kan je een gameObject adden aan meerdere scenes dus niet een bomberman creeren voor elke scene