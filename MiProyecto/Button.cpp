// Button.cpp
#include "Button.h"
#include "Game.h"
#include "raylib.h"

// Constructor
Button::Button(Rectangle r, const std::string& t, int fs, Color nc, Color hc, Color cc, Color tc, Sound hs, Sound cs, bool se, Font f)
    : rect(r), text(t), fontSize(fs), normalColor(nc), hoverColor(hc), clickColor(cc), textColor(tc),
    hoverSound(hs), clickSound(cs), soundEffectsEnabled(se), font(f), hoverSoundPlayed(false) {}

// Dibuja el boton
void Button::Draw()
{
    Vector2 mousePosition = GetMousePosition();
    Color currentColor = normalColor;
    int borderWidth = 2;

    if (CheckCollisionPointRec(mousePosition, rect))
    {
        if (!hoverSoundPlayed && soundEffectsEnabled)
        {
            PlaySound(hoverSound);
            hoverSoundPlayed = true;
        }
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            currentColor = clickColor;
            borderWidth = 5;
        }
        else
        {
            currentColor = hoverColor;
            borderWidth = 3;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && soundEffectsEnabled)
        {
            PlaySound(clickSound);
        }
    }
    else
    {
        hoverSoundPlayed = false;
    }

    DrawRectangleRec(rect, currentColor);
    DrawRectangleLinesEx(rect, borderWidth, DARKGRAY);
    int textWidth = MeasureText(text.c_str(), fontSize);
    float textX = rect.x + (rect.width - textWidth) / 2.0f;
    float textY = rect.y + (rect.height - fontSize) / 2.0f;
    DrawTextEx(font, text.c_str(), Vector2{ textX, textY }, fontSize, 0, textColor);
}

// Verifica si el boton ha sido clickeado
bool Button::IsClicked() const
{
    return IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), rect);
}

// Cambia el texto del boton
void Button::SetText(const std::string& t) { text = t; }
