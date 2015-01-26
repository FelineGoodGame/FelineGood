// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <sstream>

#define LOG Message{}

class Message
{
public:

	Message() = default;
	~Message();

	template<typename T>
	Message& operator<<(T data)
	{
		Text << data;
		return *this;
	}

	template<>
	Message& operator<<<const TCHAR*>(const TCHAR* data)
	{
		Text << TCHAR_TO_ANSI(data);
		return *this;
	}

	template<>
	Message& operator<<<FString>(FString data)
	{
		return operator<<(*data);
	}

	template<>
	Message& operator<<<FName>(FName data)
	{
		return operator<<(data.ToString());
	}

	template<>
	Message& operator<<<FText>(FText data)
	{
		return operator<<(data.ToString());
	}

private:

	std::ostringstream Text;
};
