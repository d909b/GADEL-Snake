%include <factory.i>

%factory(Actor*, TextActor, Camera, PhysicsActor, ParticleActor);
%factory(DeveloperLog*, ConsoleLog, CompoundLog, FileLog, SystemLog);
%factory(MessageListener*, TextActor, PhysicsActor, Camera, ParticleActor, Actor);
%factory(Renderable*, TextActor, PhysicsActor, Camera, ParticleActor, Actor);