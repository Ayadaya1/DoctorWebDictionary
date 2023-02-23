//В качестве альтернативы прикладываю ссылку на репозиторий с этим же проектом: https://github.com/Ayadaya1/DoctorWebDictionary
#include <vector>
#include <iostream>
#include <locale.h>

template<class Key>
class not_found_exception : public std::exception
{
public:
    virtual const Key& get_key() const noexcept = 0;
};
template<class Key>
class Not_Found_Exception : public not_found_exception<Key>
{
    Key key;
public:
    Not_Found_Exception(const Key& p_key)
    {
        key = p_key;
    }
    const Key& get_key() const noexcept override
    {
        return key;
    }
};

template<class Key, class Value>
class dictionary
{
public:
    virtual ~dictionary() = default;

    virtual const Value& get(const Key& key) const = 0;
    virtual void set(const Key& key, const Value& value) = 0;
    virtual bool is_set(const Key& key) const = 0;
};
template<class Key, class Value>
class Dictionary :public dictionary<Key,Value>
{
    std::vector<Key> keys = std::vector<Key>();
    std::vector<Value> values = std::vector<Value>();
public:
    virtual ~Dictionary() = default;

    const Value& get(const Key& key) const override
    {
        for (int i = 0; i < keys.size(); i++)
        {
            if (key==keys[i])
            {
                return values[i];
            }
        }
        throw Not_Found_Exception<Key>(key);
    }
    void set(const Key& key, const Value& value) override
    {
        try
        {
            keys.push_back(key);
            values.push_back(value);
            std::cout << "Значение записано.\n";
        }
        catch(std::exception ex)
        {
            std::cout << "Значение не записано.\n";
        }
    }
    bool is_set(const Key& key)const override
    {
        try
        {
            get(key);
        }
        catch(Not_Found_Exception<Key> ex)
        {
            return false;
        }
        return true;
    }
};



//Демонстрация работы
int main()
{
    char* locale = setlocale(LC_ALL, "Russian");
    Dictionary<std::string, std::string> dict;
    std::string key, value;
    uint8_t menu;
    bool running = true;
    while (running)
    {
        system("cls");
        std::cout << "Демонстрация работы программы с Dictionary<std::string, std::string>\n\n";
        std::cout << "1.Метод set\n";
        std::cout << "2.Метод get\n";
        std::cout << "3.Метод is_set\n";
        std::cout << "0.Завершение работы\n\n";
        std::cout << "Выберите пункт из меню: ";
        std::cin >> menu;
        
        switch (menu)
        {
        case '1':
            std::cout << "Введите ключ для добавления: ";
            std::cin >> key;
            std::cout << "Введите значение для добавления: ";
            std::cin >> value;
            dict.set(key, value);
            system("pause");
            break;
        case '2':
            std::cout << "Введите ключ для поиска: ";
            std::cin >> key;
            try
            {
                std::cout << "Значение по ключу " << key << ": " << dict.get(key)<<std::endl;
            }
            catch (Not_Found_Exception < std::string> ex)
            {
                std::cout << "Значение по ключу " << ex.get_key() << " не найдено!\n";
            }
            system("pause");
            break;
        case '3':
            std::cout << "Введите ключ для проверки: ";
            std::cin >> key;
            std::cout << "Возвращаемое значение: " << dict.is_set(key) << std::endl;
            system("pause");
            break;
        case '0':
            running = false;

        }
    }
    
    return 0;

}

