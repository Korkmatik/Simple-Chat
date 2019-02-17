//#include "SimpleClient.hpp"
//
//#include <iostream>
//
//int main()
//{
//	SimpleClient c("127.0.0.1", 54000);
//
//	try
//	{
//		c.initialize();
//		c.run();
//	}
//	catch (const std::exception& e)
//	{
//		std::cout << e.what() << std::endl;
//		std::cin.get();
//	}
//
//	return 0;
//}