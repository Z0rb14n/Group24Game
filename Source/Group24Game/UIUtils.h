#pragma once

#include "Group24Game/Group24GamePlayerController.h"

class UIUtils
{
public:
	inline static AGroup24GamePlayerController* PlayerController;

	static void OnOpenUI();

	static void OnCloseUI();

private:
	static void EnsurePlayerController();
};
