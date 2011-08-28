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

#include <tclap/CmdLine.h>
#include "Poco/Thread.h"
#include "BacsyServer.h"
#include "MulticastResponder.h"
#include "CascadingFileConfiguration.h"
#include "ConfigurationFile.h"
#include "info.h"
#include "ArgParsingUtils.h"
#include "Environment.h"


int main(int argc, char **argv)
{
	try 
	{  
		TCLAP::CmdLine cmd("Server for the Bacsy backup system", ' ', bacsyVersion);

		TCLAP::ValueArg<std::string> configArg(
				"c",
				"configdir",
				"Directory in which to look for configuration files.",
				false,
				Environment::getDefaultConfigurationDirectory(),
				"string");
		TCLAP::MultiArg<std::string> defArg(
				"D",
				"definition",
				"Add a definition to the sources configuration. Format: [section]key=value",
				false,
				"string");

		cmd.add(configArg);
		cmd.add(defArg);

		cmd.parse(argc, argv);

		std::string configdir = configArg.getValue();
		std::vector<std::string> definitions = defArg.getValue();

		CascadingFileConfiguration configuration(configdir);
		ConfigurationFile& sourcesFile = configuration.getSourceConfig();

		ArgParsingUtils::processDefinitions(definitions, sourcesFile);

		if(!configuration.storesFileLoaded())
		{
			LOGF("No " + configdir + " stores.config file found.");
		}

		StoreManager storeManager(configuration);

		BacsyServer server(storeManager);
		server.start();

		MulticastResponder responder;
		responder.start();

	}
	catch (TCLAP::ArgException &e)  // catch any exceptions
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl; 
	}

	

}
