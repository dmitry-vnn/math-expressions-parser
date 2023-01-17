#include "../Headers/containers_utils.h"

void Containers::ReplaceAll(std::string& str, const std::string toReplace, const std::string replaceWith)
{
	std::string buf;
	std::size_t pos = 0;
	std::size_t prevPos;

	buf.reserve(str.size());

	while (true) {
		prevPos = pos;
		pos = str.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		buf.append(str, prevPos, pos - prevPos);
		buf += replaceWith;
		pos += toReplace.size();
	}

	buf.append(str, prevPos, str.size() - prevPos);
	str.swap(buf);
}
