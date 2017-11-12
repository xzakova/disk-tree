#pragma once

namespace data
{
	const char json_str[] = R"([
	{
		"name": "folder-A",
		"content": [
			{
				"name": "file-A-R",
				"size": "64"
			},
			{
				"name": "file-A-S",
				"size": "8"
			},
			{
				"name": "file-A-T",
				"size": "128"
			}
		]
	},
	{
		"name": "folder-B",
		"content": [
			{
				"name": "folder-B-G",
				"content": [
					{
						"name": "file-B-G-J",
						"size": "2B"
					},
					{
						"name": "file-B-G-K",
						"size": "16B"
					},
					{
						"name": "link-B-G-L",
						"link": "/folder-A"
					}
				]
			},
			{
				"name": "file-B-M",
				"size": "32"
			}
		]
	},
	{
		"name": "file-X",
		"size": "4B"
	},
	{
		"name": "link-Y",
		"link": "/folder-B"
	},
	{
		"name": "link-Z",
		"link": "/folder-A/file-A-S"
	}
])";

}