/*
 * Copyright (C) 2011  Ives van der Flaas
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sstream>
#include <stdexcept>
#include "Bacsy/Common/JsonHelper.h"
#include "Bacsy/Common/StringUtils.h"

namespace Bacsy
{
namespace Common
{

std::string JsonHelper::write(const Json::Value& root)
{
	Json::FastWriter writer;
	return StringUtils::rstrip(writer.write(root), "\n");	
}


Json::Value JsonHelper::read(const std::string& input)
{
	std::stringstream stream;
	stream << input;
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(stream, root))
		throw std::runtime_error("Could not parse Json input " + input);

	return root;
}

}
}
