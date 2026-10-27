#pragma once

#include "../../Kernal/COM.hh"
#include <functional>
#include <optional>
#include <string>
#include <vector>
#include <memory>

class ACommand;
class AObject;
class Event;
class IPlugin;
class ColorRGB;

#include "../../Kernal/Vec2f.hpp"
#include "../../Kernal/BoxF.hpp"

namespace UI
{

/**
 * Фреймворк будет реализовывать следующие элементы:
 * - Кнопка с 3 состояниями
 * - Переключатель
 * - Контекстное окно
 * - Пул
 * - Обычное окно
 *
 * Создание будет происходить так:
 * - Пользователь создает структуру описания того, что он хочет получить.
 *   Возможно вообще сделаю систему макросов для удобства
 * - Запрашивается интерфейс фреймворка
 * - В интерфейсе вызывается конструктор по соответствующему описанию
 * - Возвращается std::unique_ptr<AOBject> готового объекта
 */

class ADescription; // forward declaration

class ADescriptionVisitor
{
public:
    ~ADescriptionVisitor() = default;

    virtual bool doForButton( const ADescription& button )      = 0;
    virtual bool doForSwitcher( const ADescription& button )    = 0;
    virtual bool doForContextMenu( const ADescription& button ) = 0;
    virtual bool doForPoolMenu( const ADescription& button )    = 0;
    virtual bool doForWindow( const ADescription& button )      = 0;

}; // class ADescriptionVisitor

// ==============================================================
// DESCRIPTIONS
// ==============================================================

class ADescription
{
public:
    virtual bool accept( ADescriptionVisitor& visitor ) = 0;

    virtual ~ADescription() = default;

    ADescription( const ADescription& )            = delete;
    ADescription( ADescription&& )                 = delete;
    ADescription& operator=( const ADescription& ) = delete;
    ADescription& operator=( ADescription&& )      = delete;
}; // class ADescription

struct Action
{
    std::vector< std::unique_ptr< ACommand > > actions;
    std::vector< std::function< void( void ) > > callbacks;
}; // struct Action

using EventHandler = std::function< bool( const Event& ) >;

enum Direct
{
    Vertical,
    Horizontal
};
enum Role
{
    Default,
    Primary,
    Danger
};

struct ButtonDescription : public ADescription
{
    BoxF box;
    std::optional< std::string > text;
    std::optional< std::string > icon;
    Action on_press;
    std::optional< Role > role;

    bool accept( ADescriptionVisitor& visitor ) override
    {
        return visitor.doForButton( *this );
    }
}; // class ButtonDescription

struct SwitcherDescription : public ADescription
{
    BoxF box;
    std::optional< std::string > text;
    std::optional< std::string > icon;
    Action on_active;
    Action on_deactive;
    std::optional< Role > role;

    bool accept( ADescriptionVisitor& visitor ) override
    {
        return visitor.doForSwitcher( *this );
    }
}; // struct SwitcherDescription

struct ContextMenu : public ADescription
{
    Vec2f min_point;
    Direct direct;
    std::vector< std::unique_ptr< ADescription > > objects;
    std::optional< EventHandler > on_event;
    std::optional< Role > role;

    bool accept( ADescriptionVisitor& visitor ) override
    {
        return visitor.doForContextMenu( *this );
    }
}; // struct ContextMenu

struct PoolMenu : public ADescription
{
    Vec2f min_point;
    Direct direct;
    std::vector< std::unique_ptr< ADescription > > objects;
    std::optional< Role > role;

    bool accept( ADescriptionVisitor& visitor ) override
    {
        return visitor.doForPoolMenu( *this );
    }
}; // struct PoolMenu

struct Window : public ADescription
{
    BoxF box;
    std::optional< EventHandler > on_event;
    std::optional< Action > on_close;
    std::optional< std::string > label;
    std::vector< std::unique_ptr< ADescription > > objects;
    std::optional< Role > role;

    bool accept( ADescriptionVisitor& visitor ) override
    {
        return visitor.doForWindow( *this );
    }
}; // struct Window

// ==============================================================
// FRAMEWORK
// ==============================================================

class IFramework : public IPlugin
{
public:
    virtual std::unique_ptr< AObject > create( const ADescription& description )                          = 0;
    virtual void registryTheme( std::string name, const ColorRGB& primary, const ColorRGB& secondary,
                                const ColorRGB& neutral, const ColorRGB& accent, const ColorRGB& unical ) = 0;
    virtual bool setTheme( std::string name )                                                             = 0;
}; // class IFramework

}; // namespace UI
