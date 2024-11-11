#include "main_layer.h"

void MainLayer::onAttach()
{
	test_scene = new TestScene;
	test_scene->onLoad();
}

void MainLayer::onUpdate(float delta)
{
	test_scene->onUpdate(delta);
}

void MainLayer::onDetach()
{
	test_scene->onUnload();
	delete test_scene;
}

void MainLayer::onEvent(const Event& e)
{
}