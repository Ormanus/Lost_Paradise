#include <iostream>
#include <string>
#include <fstream>

struct Object
{
	int type = -1, x = -1, y = -1, w = -1, h = -1, subtype = -1;
};

int main()
{
	std::cout << "Welcome to Lost Paradise Level Creator!\n";
	int type = 0;
	do
	{
		Object o;
		std::cout << "Object type > ";
		std::cin >> o.type;
		type = o.type;
		if (type >= 0){
			std::cout << "X > ";
			std::cin >> o.x;
			std::cout << "Y > ";
			std::cin >> o.y;
			switch (type)
			{
			case 1:
				std::cout << "W > ";
				std::cin >> o.w;
				std::cout << "H > ";
				std::cin >> o.h;
				std::cout << "Texture > ";
				std::cin >> o.subtype;
				break;
			}
			std::ofstream out("level.txt", std::ios::binary|std::ios::app);
			if (out)
			{
				out.write((char*)&o.type, sizeof(int));
				out.write((char*)&o.x, sizeof(int));
				out.write((char*)&o.y, sizeof(int));
				if (o.w != -1)
				{
					out.write((char*)&o.w, sizeof(int));
					out.write((char*)&o.h, sizeof(int));
				}
				if (o.subtype != -1)
				{
					out.write((char*)&o.subtype, sizeof(int));
				}
			}
		}
	} while (type != -1);
	return 0;
}