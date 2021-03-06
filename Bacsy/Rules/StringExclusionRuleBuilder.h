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

#ifndef BACSY_STRING_EXCLUSION_RULE_BUILDER_H
#define BACSY_STRING_EXCLUSION_RULE_BUILDER_H

#include "Poco/RegularExpression.h"
#include "Bacsy/Rules/ExclusionRule.h"

namespace Bacsy
{
namespace Rules
{

using namespace Common;


class StringExclusionRuleBuilder
{
public:
	static ExclusionRule build(const std::string& source);
	static bool isPath(std::string s);

private:
	static void addSize(
			ExclusionRule& rule,
			const std::string& subject,
			const bool negated);

	static void addDate(
			const Poco::RegularExpression& regex,
			ExclusionRule& rule,
			const std::string& subject,
			const bool negated);
};

}
}
#endif
