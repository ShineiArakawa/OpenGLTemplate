#pragma once
#ifndef _APP_PONE_MAIN_H_
#define _APP_PONE_MAIN_H_

#include <App/common.hpp>

static const char* WIN_TITLE = "Pone";
static pPoneModel model = nullptr;

void keyboardEventPone(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif