/*  Copyright (C) 2014-2020 FastoGT. All right reserved.
    This file is part of fastocloud.
    fastocloud is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    fastocloud is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with fastocloud.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "base/rsvg_logo.h"

#include <string>

#include <json-c/json_object.h>
#include <json-c/json_tokener.h>

#include <common/sprintf.h>

#include "base/constants.h"

#define LOGO_PATH_FIELD "path"
#define LOGO_POSITION_FIELD "position"
#define LOGO_SIZE_FIELD "size"

namespace fastocloud {

RSVGLogo::RSVGLogo() : RSVGLogo(common::uri::Url(), common::draw::Point()) {}

RSVGLogo::RSVGLogo(const common::uri::Url& path, const common::draw::Point& position)
    : path_(path), position_(position), size_() {}

bool RSVGLogo::Equals(const RSVGLogo& inf) const {
  return path_ == inf.path_;
}

common::uri::Url RSVGLogo::GetPath() const {
  return path_;
}

void RSVGLogo::SetPath(const common::uri::Url& path) {
  path_ = path;
}

common::draw::Point RSVGLogo::GetPosition() const {
  return position_;
}

void RSVGLogo::SetPosition(const common::draw::Point& position) {
  position_ = position;
}

RSVGLogo::image_size_t RSVGLogo::GetSize() const {
  return size_;
}

void RSVGLogo::SetSize(const image_size_t& size) {
  size_ = size;
}

common::Optional<RSVGLogo> RSVGLogo::MakeLogo(common::HashValue* hash) {
  if (!hash) {
    return common::Optional<RSVGLogo>();
  }

  RSVGLogo res;
  common::Value* logo_path_field = hash->Find(LOGO_PATH_FIELD);
  std::string logo_path;
  if (logo_path_field && logo_path_field->GetAsBasicString(&logo_path)) {
    res.SetPath(common::uri::Url(logo_path));
  }

  common::Value* logo_pos_field = hash->Find(LOGO_POSITION_FIELD);
  std::string logo_pos_str;
  if (logo_pos_field && logo_pos_field->GetAsBasicString(&logo_pos_str)) {
    common::draw::Point pt;
    if (common::ConvertFromString(logo_pos_str, &pt)) {
      res.SetPosition(pt);
    }
  }

  common::Value* logo_size_field = hash->Find(LOGO_SIZE_FIELD);
  std::string logo_size_str;
  if (logo_size_field && logo_size_field->GetAsBasicString(&logo_size_str)) {
    common::draw::Size sz;
    if (common::ConvertFromString(logo_size_str, &sz)) {
      res.SetSize(sz);
    }
  }

  return res;
}

common::Error RSVGLogo::DoDeSerialize(json_object* serialized) {
  fastocloud::RSVGLogo res;
  json_object* jpath = nullptr;
  json_bool jpath_exists = json_object_object_get_ex(serialized, LOGO_PATH_FIELD, &jpath);
  if (jpath_exists) {
    res.SetPath(common::uri::Url(json_object_get_string(jpath)));
  }

  json_object* jposition = nullptr;
  json_bool jposition_exists = json_object_object_get_ex(serialized, LOGO_POSITION_FIELD, &jposition);
  if (jposition_exists) {
    common::draw::Point pt;
    if (common::ConvertFromString(json_object_get_string(jposition), &pt)) {
      res.SetPosition(pt);
    }
  }

  json_object* jsize = nullptr;
  json_bool jsize_exists = json_object_object_get_ex(serialized, LOGO_SIZE_FIELD, &jsize);
  if (jsize_exists) {
    common::draw::Size sz;
    if (common::ConvertFromString(json_object_get_string(jsize), &sz)) {
      res.SetSize(sz);
    }
  }

  *this = res;
  return common::Error();
}

common::Error RSVGLogo::SerializeFields(json_object* out) const {
  const std::string logo_path = path_.GetUrl();
  json_object_object_add(out, LOGO_PATH_FIELD, json_object_new_string(logo_path.c_str()));
  const std::string position_str = common::ConvertToString(GetPosition());
  json_object_object_add(out, LOGO_POSITION_FIELD, json_object_new_string(position_str.c_str()));
  if (size_) {
    std::string size_str = common::ConvertToString(*size_);
    json_object_object_add(out, LOGO_SIZE_FIELD, json_object_new_string(size_str.c_str()));
  }

  return common::Error();
}

}  // namespace fastocloud
