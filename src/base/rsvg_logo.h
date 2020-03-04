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

#pragma once

#include <string>

#include <common/draw/types.h>
#include <common/serializer/json_serializer.h>
#include <common/uri/url.h>
#include <common/value.h>

#include "base/types.h"

namespace fastocloud {

class RSVGLogo : public common::serializer::JsonSerializer<RSVGLogo> {
 public:
  typedef common::Optional<common::draw::Size> image_size_t;
  RSVGLogo();
  RSVGLogo(const common::uri::Url& path, const common::draw::Point& position);

  bool Equals(const RSVGLogo& logo) const;

  common::uri::Url GetPath() const;
  void SetPath(const common::uri::Url& path);

  common::draw::Point GetPosition() const;
  void SetPosition(const common::draw::Point& position);

  image_size_t GetSize() const;
  void SetSize(const image_size_t& size);

  static common::Optional<RSVGLogo> MakeLogo(common::HashValue* value);

 protected:
  common::Error DoDeSerialize(json_object* serialized) override;
  common::Error SerializeFields(json_object* out) const override;

 private:
  common::uri::Url path_;
  common::draw::Point position_;
  image_size_t size_;
};

}  // namespace fastocloud
