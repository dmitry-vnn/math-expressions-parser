#pragma once

#include <string>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>

class Containers {

public:
	static void ReplaceAll(std::string& str, const std::string toReplace, const std::string replaceWith);
	
	template<class T, class V>
	static bool VectorContains(const std::vector<T>& v, const V& element);

	template<class T, class V>
	static bool VectorContains(const std::vector<std::shared_ptr<T>>& v, const V& element);

	template<class T, class V>
	static bool SetContains(const std::set<T>& s, const V& element);

	template<class T, class V>
	static std::shared_ptr<T> VectorFind(const std::vector<std::shared_ptr<T>>& v, const V& element);

	template<class T, class V>
	static T VectorFind(const std::vector<T>& v, const V& element);

	template<class T, class V>
	static std::shared_ptr<T> SetFind(const std::set<std::shared_ptr<T>>& v, const V& element);

	template<class T, class V>
	static T SetFind(const std::set<T>& v, const V& element);




private:

	Containers() = delete;
	Containers(const Containers& collections) = delete;


};

template<class T, class V>
inline bool Containers::VectorContains(const std::vector<T>& v, const V& element) 
{
	return !v.empty() && std::find(v.begin(), v.end(), element) != v.end();
}

template<class T, class V>
inline bool Containers::VectorContains(const std::vector<std::shared_ptr<T>>& v, const V& element)
{
	for (const auto& shp : v) {
		if (shp->operator==(element)) {
			return true;
		}
	}

	return false;
}

template<class T, class V>
inline bool Containers::SetContains(const std::set<T>& s, const V& element) 
{
	return !s.empty() && s.find(element) != s.end();
}

template<class T, class V>
inline std::shared_ptr<T> Containers::VectorFind(const std::vector<std::shared_ptr<T>>& v, const V& element)
{
	for (const auto& shp : v) {
		if (shp->operator==(element)) {
			return shp;
		}
	}

	throw "Not Found";
}

template<class T, class V>
inline T Containers::VectorFind(const std::vector<T>& v, const V& element)
{

	if (v.empty()) {
		throw "Not Found";
	}

	auto iter = std::find(v.begin(), v.end(), element);

	if (iter == v.end()) {
		throw "Not Found";
	}

	return *iter;
}

template<class T, class V>
inline std::shared_ptr<T> Containers::SetFind(const std::set<std::shared_ptr<T>>& v, const V& element)
{
	for (const auto& shp : v) {
		if (shp->operator==(element)) {
			return shp;
		}
	}

	throw "Not Found";
}

template<class T, class V>
inline T Containers::SetFind(const std::set<T>& v, const V& element)
{

	if (v.empty()) {
		throw "Not Found";
	}

	auto iter = std::find(v.begin(), v.end(), element);

	if (iter == v.end()) {
		throw "Not Found";
	}

	return *iter;
}