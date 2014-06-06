#include <iostream>
#include <string>
#include <vector>
#include <regex>
using namespace std;

int main()
{

	R"(The String Data \ Stuff " )";

	const char *reg_esp = "[ ,.\\t\\n;:]";  // 分隔字元列表

	std::regex rgx(reg_esp);  // regex类是模版类basic_regex以型别参数为char的具现化
	std::cmatch match;        // cmatch是模版类match_results以型别参数为const char *的具现化
	const char *target = "Polytechnic University of Turin ";

	// 辨別所有被分隔字元所分隔的字
	if (regex_search(target, match, rgx))
	{
		// 若存在
		const size_t n = match.size();
		for (size_t a = 0; a < n; a++)
		{
			string str(match[a].first, match[a].second);
			cout << str << "\n";
		}
	}

	getchar();
	return 0;
}