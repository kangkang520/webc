#pragma once
#ifndef WEBC_SERVER_CONFIG_H
#define WEBC_SERVER_CONFIG_H

#include <iostream>
#include "../utils/json.hpp"


namespace webc {
	namespace server {
		namespace config {
			webc::utils::json::Value get_config(std::string = "./config.json");
		}
	}
}


#endif // !WEBC_SERVER_CONFIG_H
