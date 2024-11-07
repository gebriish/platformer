#pragma once
#include <core/event.h>
#include <scene/camera.h>

void camera_controller_locomotion(Camera2D& camera, float deltaTime);
void camera_controller_onEvent(Camera2D& camera, const Event& e);