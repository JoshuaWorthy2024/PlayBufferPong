#include "ItemHandler.h"

#include "GroundItem.h"
#include "Grid.h"
#include "Player.h"
#include "vector"
#include "Game.h"
#include "StarterHouse.h"

std::string ItemHandler::GetItemName(int id)
{
    switch (id)
    {
        case -1:
        {
            return "None";
        }
        case 0:
        {
            return "Poke Ball";
        }
        case 1:
        {
            return "Master Ball";
        }
        case 2:
        {
            return "Ultra Ball";
        }
    }
}

std::string ItemHandler::GetSpriteName(int id)
{
    switch (id)
    {
        case 0:
        {
            return "item_ballregular";
        }
        case 1:
        {
            return "item_ballmaster";
        }
        case 2:
        {
            return "item_ballultra";
        }
    }
}

void ItemHandler::PickupGroundItem(GridCell* cell)
{
    if (m_CullingItems)
    {
        std::cout << "Busy culling items..." << std::endl;
        return;
    }
    GroundItem* item = nullptr;
    for (GroundItem* i : m_GroundItems)
    {
        if (i)
        {
            if (!i->IsShowing() || i->IsPickingUp())
            {
                continue;
            }
            if (i->GetGridCell() == cell)
            {
                i->SetPickingUp(true);
                item = i;
                break;
            }
        }
    }

    if (item == nullptr)
    {
        std::cout << "Item not found." << " at " << cell->GetRow() << ", " << cell->GetColumn() << std::endl;
        return;
    }

    if (Game::GetInstance().GetStarterHouse()->IsStarterPokemonBall(item->GetGridCell()->GetRow(), item->GetGridCell()->GetColumn(), Game::GetInstance().GetPlayer()))
    {
        return;
    }
    Game::GetInstance().GetPlayer()->AddToInventory(item->GetId(), item->GetAmount());
    item->SetShow(false);
    std::cout << "Picking up " << item->GetName() << " at " << item->GetGridCell()->GetRow() << ", " << item->GetGridCell()->GetColumn() << std::endl;
}

void ItemHandler::AddGroundItem(int id, int amount, Grid* grid, int row, int column)
{
    GroundItem* item = new GroundItem(id, amount);
    if (grid->MakeGroundItem(item, row, column))
    {
        m_GroundItems.push_back(item);
    }
}

void ItemHandler::AddGroundItem(GroundItem* item, Grid* grid, int row, int column)
{
    if (grid->MakeGroundItem(item, row, column))
    {
        m_GroundItems.push_back(item);
    }
}

void ItemHandler::DrawAll()
{
    CullGroundItems();
    if (m_GroundItems.empty())
    {
        return;
    }
    for (GroundItem* item : m_GroundItems)
    {
        if (item->IsShowing())
        {
            if (item->GetGridCell())
            {
                if (item->GetGridCell()->GetGrid())
                {
                    if (item->GetGridCell()->GetGrid()->IsActive())
                    {
                        item->Draw();
                    }
                }
            }
        }
    }
}

void ItemHandler::UpdateAll(float elapsedTime)
{

}

void ItemHandler::CullGroundItems()
{
    if (!m_PendingGroundItemsToBeRemoved.empty())
    {
        m_CullingItems = true;
        for (GroundItem* item : m_PendingGroundItemsToBeRemoved)
        {
            auto iter = std::find(m_GroundItems.begin(), m_GroundItems.end(), item);
            if (iter != m_GroundItems.end())
            {
                if (!(*iter)->IsShowing())
                {
                    m_GroundItems.erase(iter);
                    std::cout << "Removed ground item: " << item << " from m_GroundItems" << std::endl;
                }
            }
        }
        m_CullingItems = false;
    }
}
