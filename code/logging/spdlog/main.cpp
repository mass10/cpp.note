#include <stdio.h>

// [/usr/local/include/spdlog]
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>

int main() {

	auto logger = spdlog::rotating_logger_mt(
		"myapp1" /* カテゴリー */,
		"logs/rotating.txt" /* ファイル名。ディレクトリは自然に作成されます。 */,
		1024 /* これを超えないようにファイルが切られる */,
		3 /* バックアップの数 */);

	logger->info("### START ###");

	for (int i = 0; i < 10; i++ ) {
		logger->info("(operating...)");
	}

	logger->info("--- END ---");
}

