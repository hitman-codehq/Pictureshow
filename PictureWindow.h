
#ifndef PICTUREWINDOW_H
#define PICTUREWINDOW_H

#include <StdWindow.h>

class CPictureWindow : public CWindow
{
public:

	CPictureWindow(RApplication *application) : CWindow(application) { }

	void HandleCommand(int a_command) override;
};

#endif /* ! PICTUREWINDOW_H */
