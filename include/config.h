#pragma once
#include <unordered_map>
#include <iostream>
#include <string>

class RpcConfig
{
public:
    void LoadConfigFile(const char* config_file)
    {
        FILE *pf = fopen(config_file,"r");
        if(pf == nullptr)
        {
            std::cout<< config_file << "is note exist!" <<std::endl;
            exit(EXIT_FAILURE);
        }
        while (!feof(pf))
        {
            char buf[512] = {0};
            fgets(buf, 512, pf);

            std::string str(buf);
            //去除字符串前后多余的空格
            Trim(str);

            //判断#的注释
            if(str[0] == '#' || str.empty())
            {
                continue;
            }

            //解析配置项
            int index = str.find('=');
            if(index == -1)
            {
                continue;
            }

            std::string key, value;
            key = str.substr(0,index);
            Trim(key);

            int endIndex = str.find('\n',index);
            value = str.substr(index + 1, endIndex - index - 1);
            Trim(value);

            config_map.insert({key,value});
        }
        fclose(pf);
        
    }
    std::string Load(const std::string &key)
    {
        auto it =config_map.find(key);
        if(it == config_map.end())
        {
            return "";
        }
        return it->second;
    }
private:
    void Trim(std::string& str)
    {
        int index = str.find_first_not_of(' ');
        if(index != -1)
        {
            str = str.substr(index,str.size() - index);
        }
        index = str.find_last_not_of(' ');
        if(index != -1)
        {
            str = str.substr(0,index + 1);
        }
    }
private:
    std::unordered_map<std::string,std::string> config_map;
};