#include <iostream>
#include "ProjectData.h"


int main() {

	ProjectData myProject1 = ProjectData("myProject1");
	ProjectData myProject2 = ProjectData("myProject2");
	ProjectData myProject3 = ProjectData("myProject3");

	myProject1.Save();
	myProject2.Save();
	myProject3.Save();

	ProjectData LoadedProject = ProjectData();
	LoadedProject.Load("myProject2");

	LoadedProject.SetNumber(3);
	std::cout << LoadedProject.GetName() << std::endl;
	std::cout << std::to_string(LoadedProject.GetNumber()) << std::endl;


	return 0;
}