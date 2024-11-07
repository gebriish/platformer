#include "editor_layer.h"

#include "shader_utils.h"
#include "editor_utils.h"

#include "tools/camera_controller.h"

void EditorLayer::onAttach()
{
	m_EditorCamera.size = {float(window.width), float(window.height)};
	m_GameCamera.size = {float(window.width), float(window.height)};

	m_GameCamera.scale = 0.5f;

	m_SpriteBatch = new SpriteBatch(512);
	m_LineBatch = new LineBatch2d(512);

	load_glsl_shader("res/sprite.vert", "res/sprite.frag", m_SpriteShader);
	load_glsl_shader("res/line.vert", "res/line.frag", m_LineShader);
}

void EditorLayer::onDetach()
{
	delete_shader_program(m_LineShader);
	delete_shader_program(m_SpriteShader);

	delete m_SpriteBatch;
	delete m_LineBatch;
}

void EditorLayer::onUpdate(float deltaTime)
{

	if(m_State.active)
	{
		_editor_update(deltaTime);
	}
	else 
	{
		_game_update(deltaTime);
	}
}

void EditorLayer::onEvent(const Event& e)
{
	camera_controller_onEvent(m_EditorCamera, e);
	if(e.type == EventType::KEY_CLICK)
	{
		switch(e.keyData.key)
		{
			case KEY_F1:
				if(e.keyData.action == PRESS)
				{
					m_State.active = !m_State.active;
					printf("Editor Active (%d)\n", (int) m_State.active);
				}
			break;
		}
	}
}

void EditorLayer::onEditorStateChange(const EditorStateEvent& e)
{

} 


void EditorLayer::_editor_update(float deltaTime)
{
	auto[x, y] = Input::getCursorPosition();

	camera_controller_locomotion(m_EditorCamera, deltaTime);

	clear_viewport(m_State.preferences.Colors[BACKGROUND]);

	//-------------------------------------------------------------

	m_LineBatch->beginBatch();
	
	Line2d grid_line;

	{
		grid_line.begin = vec2(m_EditorCamera.position.x - m_EditorCamera.size.x * m_EditorCamera.scale, 0);
		grid_line.end   = vec2(m_EditorCamera.position.x + m_EditorCamera.size.x * m_EditorCamera.scale, 0);
		grid_line.color = m_State.preferences.Colors[RED_1];
		
		add_editor_line(m_LineBatch, m_LineShader, m_EditorCamera, grid_line);



		grid_line.begin = vec2(0, m_EditorCamera.position.y - m_EditorCamera.size.y * m_EditorCamera.scale);
		grid_line.end   = vec2(0, m_EditorCamera.position.y + m_EditorCamera.size.y * m_EditorCamera.scale);
		grid_line.color = m_State.preferences.Colors[GREEN_1];
		
		add_editor_line(m_LineBatch, m_LineShader, m_EditorCamera, grid_line);
	
	}


	unsigned int debug_grid = std::ceil(m_EditorCamera.scale * 1/3.0) * m_State.preferences.GRID_SIZE;

	vec2 min, max;
	min = nearest_grid_floor(m_EditorCamera.position - m_EditorCamera.size * 0.5 * m_EditorCamera.scale, debug_grid);
	max = nearest_grid_ceil(m_EditorCamera.position + m_EditorCamera.size * 0.5 * m_EditorCamera.scale, debug_grid);

	for(float x = min.x; x < max.x; x += debug_grid)
	{
		for(float y = min.y; y < max.y; y += debug_grid)
		{
			float scale = 3.0;
			//if(x == 0 || y == 0) continue;

			grid_line.color = m_State.preferences.Colors[GRAY_2];

			grid_line.begin = vec2{x, y} - vec2{m_EditorCamera.scale * scale};
			grid_line.end   = vec2{x, y} + vec2{m_EditorCamera.scale * scale};
			
			add_editor_line(m_LineBatch, m_LineShader, m_EditorCamera, grid_line);

			grid_line.begin = vec2{x, y} - vec2{m_EditorCamera.scale * scale, -m_EditorCamera.scale * scale};
			grid_line.end   = vec2{x, y} + vec2{m_EditorCamera.scale * scale, -m_EditorCamera.scale * scale};
			
			add_editor_line(m_LineBatch, m_LineShader, m_EditorCamera, grid_line);
		}
	}

	add_editor_box(m_LineBatch, m_LineShader, m_EditorCamera, m_GameCamera.position, m_GameCamera.size * m_GameCamera.scale, m_State.preferences.Colors[GRAY_2]);
	
	add_editor_box(m_LineBatch, m_LineShader, m_EditorCamera, nearest_grid(m_EditorCamera.screenToWorld(x, y), m_State.preferences.GRID_SIZE), vec2(m_State.preferences.GRID_SIZE), m_State.preferences.Colors[GREEN_2]);

	m_LineBatch->endBatch();

	use_shader_program(m_LineShader);
	shader_upload_camera2d_data(m_LineShader, m_EditorCamera);
	m_LineBatch->drawBatch();

	//-------------------------------------------------------------

	m_SpriteBatch->beginBatch();

	Sprite s;
	s.size = {32};
	m_SpriteBatch->addSprite(s);

	m_SpriteBatch->endBatch();

	use_shader_program(m_SpriteShader);
	shader_upload_camera2d_data(m_SpriteShader, m_EditorCamera);
	m_SpriteBatch->drawBatch();
}

void EditorLayer::_game_update(float deltaTime)
{
	clear_viewport({0x13, 0x13, 0x13, 0xff});
}

