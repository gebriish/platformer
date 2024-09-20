#pragma once

#include <core/application.h>

namespace APP
{
	class SandboxApp : public ENGINE::Application
	{
	protected:
		virtual void Init() override;
		virtual void Update(f32 dt) override;
		virtual void Cleanup() override;

	};
}