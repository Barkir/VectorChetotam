#pragma once

#include "CommonClass.hh"
#include <charconv>
#include <cstdint>
#include <memory>
#include <list>

// Event
struct Event;

// Object
class AObject
{
private:
    FBox _box;
    std::list< std::unique_ptr< AObject > > _children;
    AObject* _parent;

public:
    // Common
    void setParent( AObject* new_parent );
    AObject* getParent() const;
    std::list< std::unique_ptr< AObject > > getChildren();

    // Logic
    virtual bool processEvent( const Event& event ) = 0;
    virtual void run()                              = 0; // use App

    // Render
    virtual void render() = 0; // use App

}; // class AObject

/**
 * Для AObject:
 */

/**
 * С render сейчас не очень понятно. Я думаю, все текстуры необходимо хранить в render, что бы они не уходили наружу.
 * Отрисовка только по ID.
 *
 * (?) Нужно ли добавлять отдельно цвета или их также регистрировать через render. В принципе - обход есть : если мы
 * храним в ID тип ресурса (например 2 байта) и место на идентификатор ресурса >= 4 байт, то можно хранить цвет прямо в
 * ID.
 *
 * Вопросы на будущее:
 * (?) Стоит ли добавлять фильтры и маски (например для рисования круга с текстурой можно использовать маску круга и
 * такой способ распространяется на любой объект).
 * (?) Как происходит рисование текста? Производим ли мы автоматическое выравнивание, перенос новой линии.
 * Поддерживается ли рисование по линии.
 * (?) Как будет реализовано рисование spline? Массив точек + метод аппроксимации?
 */
class IRenderer
{
public:
    using ResourceID = uint64_t;

    virtual void drawRect( const ResourceID& color, const FBox& box, const float& angle )      = 0;
    virtual void drawTexture( const ResourceID& texture, const FBox& box, const float& angle ) = 0;
    virtual void drawCircle( const ResourceID& color, const FBox& box )                        = 0;

    virtual void update() = 0; // not for latte coffee raylib users(lamers)
    virtual void clear()  = 0;

    // Есть предложение использовать отдельный класс TextPreference вместо множества аргументов, но это дополнительная
    // зависимость
    virtual void drawText( const char* text, const ResourceID& color, const FBox& box ) = 0;

}; // class IRender

/**
 * Я точно не помню, что мы выбрали - 1 или 2 функции.
 */
class IInputPump
{
public:
    virtual bool pullEvent( Event& event ) = 0;
}; // class IInputPump

class IUIManager
{
    /**
     * Можно задавать все объекты для UI через JSON
     * Кароче, нам нужно:
     * Кнопка Стандартная. На переднем плане текст и|или картинка
     * Кнопка Зажимная. Данные аналогично обычной
     *
     */

}; // class IUIManager

class App
{
public:
    App( const App& )            = delete;
    App( App&& )                 = delete;
    App& operator=( const App& ) = delete;
    App& operator=( App&& )      = delete;

    void setInputPump( IInputPump* input_pump );
    void setRenderer( IRenderer* render );
    void setUIManager( IUIManager* ui_manager );

    IInputPump* getInputPump() const;
    IRenderer* getRenderer() const;
    IUIManager* getUIManager() const;

    static App& instance()
    {
        static App _52;
        return _52;
    }

private:
    IInputPump* _input_pump = nullptr;
    IRenderer* _render      = nullptr;
    IUIManager* _ui_manager = nullptr;

    App()  = default;
    ~App() = default;

}; // class App
