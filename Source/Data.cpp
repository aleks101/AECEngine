#include "Data.h"

namespace AEC {
	void Data::SetFile(std::string path) {
		m_filePath = path;
		m_manager = FileManager(path);
	}
}