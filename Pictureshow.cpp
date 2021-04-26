
#include <StdFuncs.h>
#include <Args.h>
#include <StdApplication.h>
#include "Pictureshow.h"
#include "PictureWindow.h"

#ifdef __amigaos4__

#include <proto/utility.h>

/* Lovely version structure.  Only Amiga makes it possible! */

static const struct Resident g_oROMTag __attribute__((used)) =
{
	RTC_MATCHWORD,
	(struct Resident *) &g_oROMTag,
	(struct Resident *) (&g_oROMTag + 1),
	RTF_AUTOINIT,
	0,
	NT_LIBRARY,
	0,
	"Brunel",
	"\0$VER: Pictureshow v0.01 by Colin Ward AKA Hitman/Code HQ (24.04.2021)\r\n",
	NULL
};

#elif defined(__amigaos__)

const char g_accVersion[] = "$VER: Pictureshow v0.01 by Colin Ward AKA Hitman/Code HQ (24.04.2021)\r\n";

#endif /* __amigaos__ */

static SStdMenuItem g_menuItems[] =
{
	{ EStdMenuTitle, "&File", NULL, 0, 0 },

#ifdef WIN32

	{ EStdMenuItem, "E&xit", "Q", STD_KEY_MENU, EMenuFileQuit },

#else /* ! WIN32 */

	{ EStdMenuItem, "&Quit", "Q", STD_KEY_MENU, EMenuFileQuit },

#endif /* ! WIN32 */

	{ EStdMenuEnd, NULL, NULL, 0, 0 }
};

/* Template for use in obtaining command line parameters */
static const char g_accTemplate[] = "REMOTE,URL";
#define ARGS_REMOTE 0
#define ARGS_URL 1
#define ARGS_NUM_ARGS 2

RArgs g_args;	/* Contains the parsed command line arguments */

/**
 * Main application entry point.
 * Prepares the system for execution and opens the main browser window.
 *
 * @date	Saturday 24.04.2021 11:16, by the Landwehrkanal, Kreuzberg
 * @return	Always RETURN_OK (0)
 */

TFMain()
{
	int result;
	RApplication *pictureshow = new RApplication;

	/* StdFuncs error routines should use requesters, not print statements */
	g_bUsingGUI = ETrue;

	if ((result = g_args.open(g_accTemplate, ARGS_NUM_ARGS, TFArgs)) == KErrNone)
	{
		if ((result = pictureshow->open(g_menuItems)) == KErrNone)
		{
			CPictureWindow *pictureWindow = new CPictureWindow(pictureshow);

			if ((result = pictureWindow->open("Pictureshow v0.01 by Colin Ward AKA Hitman/Code HQ (24.04.2021)", "Pictureshow", ETrue)) == KErrNone)
			{
				pictureshow->Main();
			}

			delete pictureWindow;

			pictureshow->close();
		}
		else
		{
			Utils::Error("Unable to initialise Pictureshow instance (Error = %d)", result);
		}

		g_args.close();
	}
	else
	{
		if (result == KErrNotFound)
		{
			Utils::Error("Required argument missing");
		}
		else
		{
			Utils::Error("Unable to read command line arguments");
		}
	}

	delete pictureshow;

	return RETURN_OK;
}
