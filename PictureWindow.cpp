
#include <StdFuncs.h>
#include <StdApplication.h>
#include "Pictureshow.h"
#include "PictureWindow.h"

/**
 * Handles commands coming from menu items, gadgets and accelerators.
 *
 * @date	Monday 26-Apr-2021 7:29 am, Code HQ Bergmannstrasse
 * @param	a_command		The ID of the command to be processed
 */

void CPictureWindow::HandleCommand(int a_command)
{
	switch (a_command)
	{
		case IDCANCEL :
		case EMenuFileQuit :
		{
			m_poApplication->exit();
		}
	}
}
