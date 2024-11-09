#include "camera_controller.h"

#include <core/window.h>
#include <core/input.h>
#include <cmath>

vec2 cam_pos;

void camera_controller_locomotion(Camera2D& camera, float deltaTime)
{

	vec2 cam_move = {0 ,0};

    if(Input::isKeyPressed(KEY_W) && !Input::isKeyPressed(KEY_S))
        cam_move.y = 1.0f;
    if(Input::isKeyPressed(KEY_S) && !Input::isKeyPressed(KEY_W))
        cam_move.y = -1.0f;
    if(Input::isKeyPressed(KEY_D) && !Input::isKeyPressed(KEY_A))
        cam_move.x = 1.0f;
    if(Input::isKeyPressed(KEY_A) && !Input::isKeyPressed(KEY_D))
        cam_move.x = -1.0f;
	
    if(Input::isKeyPressed(KEY_E))
        camera.scale -= deltaTime;
    if(Input::isKeyPressed(KEY_Q))
        camera.scale += deltaTime;

    if(camera.scale < 1 / 32.0f)
        camera.scale = 1 / 32.0f;

    cam_move = normalize(cam_move);

    cam_pos += cam_move * 500.0f * deltaTime;

    camera.position = lerp(camera.position, cam_pos, 10 * deltaTime);
}

void camera_controller_onEvent(Camera2D& camera, const Event& e)
{
    if(e.type == EventType::CURSOR_MOVE)
    {
        if(Input::isMouseButtonPressed(1))
            cam_pos -= vec2{(float) e.cursorMoveData.Dx, (float) e.cursorMoveData.Dy} * camera.scale;
    }
}