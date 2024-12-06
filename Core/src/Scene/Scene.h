//
// Created by Lucas Täkker on 12/4/24.
//

#pragma once

#include <string>

/**
 * Note to self
 *
 * I could create a save/load base class, that this inherits from
 * I could maybe use a map (key, { T, pointer to value }) with pointers to each
 * And use a macro PROPERTY() that adds the next variable as a entry on the map
 * Then I could just write it using json (encrypted if I want)
 */


class Scene {
public:
	Scene(std::string fileName);
	Scene();
	~Scene();

	void Update(float deltaTime);

	// Filesystem
	void SaveNew(std::string fileName);
	void Save();
	void ResetToFile();

private:
	std::string m_fileName;

	// std::vector<Object> m_objects;
};
