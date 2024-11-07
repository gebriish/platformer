#pragma once
#include <core/layer.h>
#include <core/application.h>

#include <core/window.h>
#include <core/input.h>

#include <scene/camera.h>

#include <graphics/shader.h>
#include <graphics/line_batch2d.h>
#include <graphics/sprite_batch.h>

enum ColorCodes
{
	BACKGROUND 	= 0,
	RED_1 		= 1,
	GREEN_1 	= 2,
	YELLOW_1 	= 3,
	BLUE_1 		= 4,
	PURPLE_1 	= 5,
	AQUA_1 		= 6,
	GRAY_1 		= 7,

	GRAY_2 		= 8,
	RED_2 		= 9,
	GREEN_2 	= 10,
	YELLOW_2 	= 11,
	BLUE_2 		= 12,
	PURPLE_2 	= 13,
	AQUA_2 		= 14,
	FORGROUND 	= 15,

	SIZE 		= 16,
};


enum class EditorStateEventType
{
	COLOR_CHANGE,
};

enum class EditorStateMode
{
	NAV,

};

struct EditorStateEvent
{
	EditorStateEventType type;
	std::pair<EditorStateMode, EditorStateMode> mode; 
};

struct EditorState
{
	bool active = true;
	bool camera_drag_move = false;

	struct 
	{
		unsigned int GRID_SIZE = 32;

		Color Colors[ColorCodes::SIZE] {
			Color {0x1d, 0x20, 0x21, 0xff},
			Color {0xcc, 0x24, 0x1d, 0xff},
			Color {0x98, 0x97, 0x1a, 0xff},
			Color {0xd7, 0x99, 0x21, 0xff},
			Color {0x45, 0x85, 0x88, 0xff},
			Color {0xb1, 0x62, 0x86, 0xff},
			Color {0x68, 0x9d, 0x6a, 0xff},
			Color {0xa8, 0x99, 0x84, 0xff},

			Color {0x92, 0x83, 0x74, 0xff},
			Color {0xfb, 0x49, 0x34, 0xff},
			Color {0xb8, 0xbb, 0x26, 0xff},
			Color {0xfa, 0xbd, 0x2f, 0xff},
			Color {0x83, 0xa5, 0x98, 0xff},
			Color {0xd3, 0x86, 0x9b, 0xff},
			Color {0x8e, 0xc0, 0x7c, 0xff},
			Color {0xeb, 0xdb, 0xb2, 0xff},
		};

	} preferences;
};

class EditorLayer : public Layer 
{
public:
	virtual void onAttach() override;
	virtual void onDetach() override;
	virtual void onUpdate(float deltaTime) override;
	virtual void onEvent(const Event& e) override;
	
	void onEditorStateChange(const EditorStateEvent& e);

private:
	void _editor_update(float deltaTime);
	void _game_update(float deltaTime);

private:
	Window &window = Application::Get().window();

	Camera2D m_EditorCamera, m_GameCamera;
	EditorState m_State;

	SpriteBatch *m_SpriteBatch;
	LineBatch2d *m_LineBatch;

	Shader m_SpriteShader;
	Shader m_LineShader;
};