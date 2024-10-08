#pragma once

#include <core/application.h>

namespace APP
{
	class SandboxApp : public ENGINE::CORE::Application
	{
	protected:
		virtual void Init() override;
		virtual void Update(f32 dt) override;
		virtual void Cleanup() override;
		virtual void OnEvent(ENGINE::CORE::Event& e) override;
	};
}
