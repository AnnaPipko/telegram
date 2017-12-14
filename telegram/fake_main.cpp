#include <iostream>

#include <telegram/fake.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " <test-case>" << std::endl;
        return 1;
    }

    telegram::FakeServer fake(argv[1]);
    fake.Start();

    std::cout << "Fake server is listening at " << fake.GetUrl() << std::endl;
    std::cin.get();

    fake.StopAndCheckExpectations();

    return 0;
}
