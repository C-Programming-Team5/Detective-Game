#include "main.h"
#include "screen.h"
#include "save_io.h"

int main(void)
{
	int selected = 0;
	Player *save = InitSave();
	selected = StartScreen();
	switch (selected)
	{
		case 0:
			break;
		case 1:
			if (LoadFromFile(save) == 0)
			{
				perror("파일을 불러올 수 없습니다.\n");
				return 1;
			}
			PrintSaveList(save);
			break;
		default:
			break;
	}
	return 0;
}

