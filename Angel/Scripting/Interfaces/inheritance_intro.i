%include <factory.i>

%factory(Actor*, TextActor, MazeFinder, Camera, PhysicsActor, ParticleActor);
%factory(DeveloperLog*, ConsoleLog, CompoundLog, FileLog, SystemLog);
%factory(MessageListener*, TextActor, MazeFinder, Camera, PhysicsActor, ParticleActor, Actor);
%factory(Renderable*, TextActor, MazeFinder, Camera, PhysicsActor, ParticleActor, Actor);