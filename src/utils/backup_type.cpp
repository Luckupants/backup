#include "backup_type.hpp"

#include <exception>
#include <format>

#include <boost/filesystem/fstream.hpp>

namespace utils {

std::string GetBackupTag(const filesystem::path& path) {
  const auto tag_path = path / kBackupTag;
  filesystem::ifstream tag_stream(tag_path);
  if (!tag_stream.is_open()) {
    throw std::runtime_error(
        std::format("can't read {} to verify backup type", tag_path.string()));
  }
  std::string tag;
  tag_stream >> tag;
  return tag;
}

void MakeBackupTag(const filesystem::path& path, std::string_view tag) {
  filesystem::ofstream backup_tag(path / kBackupTag);
  backup_tag << tag;
  backup_tag.close();
}

}  // namespace utils
