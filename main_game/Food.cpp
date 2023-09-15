#include "Food.h"

#include "Config.h"

Food::Food(const Vector2Int startPosition, const iki_color startColor)
    :
    isEaten(false),
    pos(startPosition),
    color(startColor),
    rect({0, 0, 0, 0})
{}

Food::~Food()
{
}

bool Food::IsEaten() const
{
    return isEaten;
}

void Food::Eaten()
{
    isEaten = true;
}

Vector2Int Food::GetPosition() const
{
    return pos;
}

void Food::SetPosition(const Vector2Int newPos)
{
    pos = newPos;
}

void Food::Update(float dt, const Map map)
{
    if (isEaten)
    {
        isEaten = false;
    }

    rect.left = pos.x * ((CANVAS_WIDTH / map.GetWidth())) + 1;
    rect.top = pos.y * ((CANVAS_WIDTH / map.GetHeight())) + 1;
    rect.right = ((CANVAS_WIDTH / map.GetWidth()) - 1);
    rect.bottom = ((CANVAS_HEIGHT / map.GetHeight()) - 1);
}

void Food::Draw()
{
    DrawRect(rect, {0, 0, CANVAS_WIDTH, CANVAS_HEIGHT}, color);
}
