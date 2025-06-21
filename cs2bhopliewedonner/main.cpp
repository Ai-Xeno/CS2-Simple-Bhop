#include "mem.h"
#include <thread>

namespace offsets
{
	constexpr auto jump = 0x184EE00;
}

int main()
{
	auto memory = mem("cs2.exe");

	std::cout << "Proc Id: " << memory.getProcId() << std::endl;

	const auto client = memory.GetModuleBaseAddress("client.dll");
	std::cout << "client.dll -> " << "0x" << std::hex << client << std::dec << std::endl;

	while (true)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			memory.Write<int>(client + offsets::jump, 65536);
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			memory.Write<int>(client + offsets::jump, 0);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}