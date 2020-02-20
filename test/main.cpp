#include <kozura/string>
#include <kozura/array>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	{
		using namespace kozura;
		kstring_t str1 = "The kozura string type";
		str1 += " is great!";

		karray_t<kstring_t> array;
		for (int i(0); i < 10; ++i) {
			char b[4];
			sprintf(b, "%d", i);
			kstring_t str2 = str1 + " " + kstring_t(b);
			array.addItem(str2);
		}

		int sz = array.size();

		karray_t<kstring_t> array2 = array;

		for (int i(0); i < 10; ++i) {
			printf("item %d value: %s\n", i, array2.at(i).c_str());
		}

		array.clear();
		array2.clear();

		karray_t<int> arrayint;
		for (int i(0); i < 10; ++i) {
			arrayint.addItem(i);
		}

		for (int i(0); i < 10; ++i) {
			printf("item %d value: %d\n", i, arrayint.at(i));
		}

		arrayint.clear();
	}

	return 0;
}
