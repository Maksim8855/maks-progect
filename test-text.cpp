#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

using namespace std;

struct enemy {
  string name;
  int health;
  int atk;
  string image;
};

struct ShopItem {
  string name;
  int price;
  int effect;
  string rarity;
};

struct catItem {
  string name;
  int quan;
  int effect;
  string rarity;
};

struct dog {
  int health;
  int atc;
  int BOShealth;
  int BOSatc;
};

struct Pet {
  string name;
  int level;
  int health;
  int xp;
  int happiness;
  int Maxhealth;
  int money;
  int atc;
  int Maxatc;
};

void drawPet(Pet myPet) {
  cout << "              __" << endl;
  cout << "             /(o" << endl;
  cout << "       ,-,  //  \\\\" << endl;
  cout << "      (,,,) ||   v" << endl;
  cout << "     (,,,,)\\//" << endl;
  cout << "     (,,,/w)-'" << endl;
  cout << "     \\,,/w)" << endl;
  cout << "     v/uu" << endl;
  cout << "       / |" << endl;
  cout << "       | |" << endl;
  cout << "       o o" << endl;
  cout << "       \\ |" << endl;
  cout << "  \\,/  ,\\|,.  \\,/" << endl;
}

void waitForEnter() {
  cout << "\033[31нажмите Enter для продолжения";
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get();
}

void displayPet(const Pet &pet, vector<catItem> &inventory) {
  cout << "\x1B[2J\x1B[H";
  cout << "NAME: " << pet.name << endl;
  cout << "LEVEL: " << pet.level << endl;
  cout << "HP: " << pet.health << endl;
  cout << "Счастье: " << pet.happiness << endl;
  cout << "XP: " << pet.xp << endl;
  cout << "MONEY $: " << pet.money << endl;
  cout << "Инвентарь: " << endl;
  unordered_map<string, int> itemQuantities;
  for (const auto &item : inventory) {
    if (item.quan > 0) {
      if (itemQuantities.find(item.name) != itemQuantities.end()) {
        itemQuantities[item.name] += item.quan;
      } else {
        itemQuantities[item.name] = item.quan;
      }
    }
  }

  for (const auto &item : itemQuantities) {
    cout << item.first << " (" << item.second << ")" << endl;
  }
  for (auto it = inventory.begin(); it != inventory.end();) {
    if (it->quan == 0) {
      cout << "Предмет " << it->name << " удален из инвентаря" << endl;
      it = inventory.erase(it);
    } else {
      ++it;
    }
  }

  drawPet(pet);
}

void displayMenu() {
  cout << "1. Играть с питомцем" << endl;
  cout << "2. Покормить питомца" << endl;
  cout << "3. Отправиться в путешествие" << endl;
  cout << "4. возвысить питомца" << endl;
  cout << "5. посетить магазин" << endl;
  cout << "6. активировать предмет" << endl;
  cout << "7. посетить арену " << endl;
  cout << "8. скрафтить предмет" << endl;
  cout << "9. Выйти из программы" << endl;
}

int playCat(Pet &pet) {
  cout << "\x1B[2J\x1B[H";
  cout << "Вы играете с питомцем " << pet.name << endl;
  pet.happiness += 10;
  pet.health -= 5;
  pet.xp += 10;
  cout << "+10 XP и -5 HP." << endl;
  cout << "Ваше счастье повысилось на 10." << endl;
  cout << "нажмите любую кнопку чтобы вернуться в меню" << endl;
  waitForEnter();
  return 0;
}

int eatCat(Pet &myPet, vector<catItem> &inventory) {
  cout << "\x1B[2J\x1B[H";
  bool isFed = false;
  for (catItem &item : inventory) {
    if (item.name == "Еда для питомца" && item.quan > 0) {
      cout << "Вы покормили питомца." << endl;
      cout << "Ваше здоровье повысилось на 10." << endl;
      myPet.health += 10;
      myPet.happiness += 5;
      myPet.xp += 5;
      item.quan--;
      isFed = true;
      if (myPet.health > myPet.Maxhealth) {
        myPet.health = myPet.Maxhealth;
      }
      break;
    }
  }
  if (!isFed) {
    cout << "У вас не хватает еды." << endl;
  }
  waitForEnter();
  return 0;
}

int battle(Pet &myPet, dog dogbattle) {
  drawPet(myPet);
  cout << endl;
  cout << "    VS     " << endl;
  cout << "        __ _" << endl;
  cout << "        \\.'---.//|" << endl;
  cout << "         |\\./| \\ " << endl;
  cout << "        _|.|.|_ \\ " << endl;
  cout << "       /( ) ' ' \\ " << endl;
  cout << "      | \\/ . | \\ " << endl;
  cout << "     \\_/\\__/| |\\ " << endl;
  cout << "          /  / |" << endl;
  cout << "          /__/ /\\ " << endl;
  cout << "          \\___/\\ " << endl;
  int x = rand() % 2;
  if (x == 0) {
    cout << "злыя собака испугались вас и сбежала (+ 20 монет)" << endl;
    myPet.happiness += 10;
    myPet.money += 20;
    myPet.xp += 25;
  }
  if (x == 1) {
    int xpdog = dogbattle.health;
    int atcdog = dogbattle.atc;
    int xpcat = myPet.health;
    int atcpet = myPet.atc;
    while (xpdog > 0) {
      cout << "\n";
      cout << "1.ударить правой ногой" << endl;
      cout << "2.ударить левой ногой" << endl;
      cout << "3.ударить головой" << endl;
      int choice;
      cin >> choice;
      if (choice == 1) {
        cout << "\x1B[2J\x1B[H";
        cout << "вы ударили правой ногой" << endl;
        xpdog -= atcpet;
        cout << "здоровье собаки уменьшилось на " << atcpet << endl;
        cout << "собака ударила вас в ответ и ваше здоровье упало на " << atcdog
             << endl;
        myPet.health = xpcat - atcdog;
      }
      if (choice == 2) {
        cout << "\x1B[2J\x1B[H";
        cout << "вы ударили левой ногой" << endl;
        xpdog -= atcpet * 1.5;
        cout << "здоровье собаки уменьшилось на " << atcpet * 1.5 << endl;
        cout << "собака ударила вас в ответ и ваше здоровье упало на " << atcdog
             << endl;
        myPet.health = xpcat - atcdog;
      }
      if (choice == 3) {
        cout << "\x1B[2J\x1B[H";
        cout << "вы ударили головой" << endl;
        xpdog -= atcpet * 2;
        cout << "здоровье собаки уменьшилось на " << atcpet * 2 << endl;
        cout << "собака ударила вас, ваше здоровье упало на " << atcdog
             << "из-за удара головой у вас сильная боль (-10 HP)"
             << "\n";
        myPet.health = xpcat - atcdog - 10;
      } else {
        cout << "вы не выбрали ни один из вариантов" << endl;
      }
    }
    if (xpdog <= 0) {
      cout << "вы победили собаку" << endl;
      cout << "+10 опыта и +20 монет" << endl;
      myPet.happiness += 10;
      myPet.xp += 10;
      myPet.money += 40;
      return 0;
    }
    if (x == 2) {
      int xpdog = dogbattle.health;
      int atcdog = dogbattle.atc;
      int xpcat = myPet.health;
      int atcpet = myPet.atc;
      while (xpdog > 0) {
        cout << "\n";
        cout << "1.ударить правой ногой\n";
        cout << "2.удар  левой ногой\n";
        cout << "3.удар головой\n";
        int choice;
        cin >> choice;
        if (choice == 1) {
          cout << "\x1B[2J\x1B[H";
          cout << "вы ударили правой ногой" << endl;
          xpdog -= atcpet;
          cout << "здоровье БОССА уменьшилось на " << atcpet << endl;
          cout << "БОСС ударил вас в ответ и ваше здоровье упало на " << atcdog
               << endl;
          myPet.health = xpcat - atcdog;
        }
        if (choice == 2) {
          cout << "\x1B[2J\x1B[H";
          cout << "вы ударили  левой ногой" << endl;
          xpdog -= atcpet * 1.5;
          cout << "здоровье БОССА уменьшилось на " << atcpet * 1.5 << endl;
          cout << "БОСС ударил вас в ответ и ваше здоровье упало на " << atcdog
               << endl;
          myPet.health = xpcat - atcdog;
        }
        if (choice == 3) {
          cout << "\x1B[2J\x1B[H";
          cout << "вы ударили головой" << endl;
          xpdog -= atcpet * 2;
          cout << "здоровье БОССА уменьшилось на " << atcpet * 2 << endl;
          cout
              << "БОСС ударил вас в ответ и ваше здоровье упало на " << atcdog
              << "из-за удара головой вы поранились и ваше здоровье упало на 10"
              << "\n";
          myPet.health = xpcat - atcdog - 10;
        } else {
          cout << "вы не выбрали ни один из вариантов" << endl;
        }
      }
      if (xpdog <= 0) {
        cout << "вы победили БОССA собак" << endl;
        cout << "вы получили 10 опыта и 20 монет" << endl;
        myPet.happiness += 10;
        myPet.xp += 10;
        myPet.money += 40;
        return 0;
      }
    }
  }
  return 0;
}

int travlCat(Pet &myPet, dog dogbattle) {
  cout << "\x1B[2J\x1B[H";
  cout << "Вы отправились в путешествие." << endl;
  cout << "+20 XP и -10 HP." << endl;
  myPet.health -= 10;
  myPet.xp += 25;
  int rand(void);
  int x = rand() % 3;
  if (x == 0) {
    cout << "Вы не смогли найти ничего и вернулись домой" << endl;
  }
  if (x == 1) {
    cout << "Вы нашли 20$ и вернулись домой (+20$)" << endl;
    myPet.money += 20;
  }
  if (x == 2) {
    cout << "на вас напали злые собаки! Пойти в драку или сбежать:" << endl;
    cout << "1. драться" << endl;
    cout << "2. сбежать" << endl;
    int a;
    cin >> a;
    if (a == 1) {
      cout << "вы решили принять бой " << endl;
      battle(myPet, dogbattle);
    } else if (a == 2) {
      int x1 = rand() % 2;
      if (x1 == 0) {
        cout << "Вы сбежали от них и вернулись в берлогу" << endl;
      } else if (x1 == 1) {
        cout << "Вы не смогли сбежать и вам откусили крыло" << endl;
        myPet.health -= 50;
      }
    } else {
      cout << "Вы ввели неверное число! В бой!" << endl;
      battle(myPet, dogbattle);
    }
  }
  waitForEnter();
  return 0;
}

int rangCat(Pet &myPet, dog &dogbattle, vector<enemy> &enemies) {
  cout << "\x1B[2J\x1B[H";
  cout << "чтобы возвысить петомца вам надо:" << 150 + myPet.level * 25
       << " XP и " << 200 + myPet.level * 25 << " счастья" << endl;
  if (myPet.xp >= 150 + myPet.level * 25 and
      myPet.happiness >= 200 + myPet.level * 25) {
    cout << "Вы возвысили своего питомца." << endl;
    myPet.level += 1;
    myPet.xp -= 150 + myPet.level * 25;
    myPet.happiness -= 200 + myPet.level * 25;
    myPet.Maxhealth += 50;
    myPet.Maxatc += 10;
    dogbattle.health += 25;
    dogbattle.atc += 10;
    for (auto &en : enemies) {
      en.atk += 5;
      en.health += 30;
    }
  } else {
    cout << "У вас недостаточно XP или счастья для возвышения питомца." << endl;
  }
  waitForEnter();
  return 0;
}

int shop(Pet &myPet, vector<ShopItem> &shopItems, vector<catItem> &inventory) {
  cout << "             //" << endl;
  cout << "             ('>" << endl;
  cout << "             /рр" << endl;
  cout << "            *\\))_" << endl;
  // cout << "|-----------------------------|" << endl;
  // cout << "|    MAGIC  HAPPY   HP    XP  |" << endl;
  // cout << "|   POTION    SWORD    SHIELD |" << endl;
  // cout << "|     FOOD     Fe     Stick   |" << endl;
  // cout << "|_____________________________|" << endl;
  cout << "У вас есть " << myPet.money << " монет." << endl;
  cout << "Вот что мы может предложить вам кролик:" << endl;
  for (int i = 0; i < shopItems.size(); i++) {
    cout << i + 1 << ". " << shopItems[i].name
         << " - Цена: " << shopItems[i].price
         << ", Эффект: " << shopItems[i].effect
         << ", Редкость: " << shopItems[i].rarity << endl;
  }
  cout << "Введите номер: ";
  int choice;
  cin >> choice;
  choice--;
  if (choice >= 0 && choice < shopItems.size()) {
    if (myPet.money >= shopItems[choice].price) {
      if (shopItems[choice].name == "Еда для питомца") {
        inventory.push_back({shopItems[choice].name, 5});
        myPet.money -= shopItems[choice].price;
        cout << "Вы успешно купили " << shopItems[choice].name << "!" << endl;
      }
      inventory.push_back({shopItems[choice].name, 1});
      myPet.money -= shopItems[choice].price;
      cout << "Вы успешно купили " << shopItems[choice].name << "!" << endl;
    } else {
      cout << "У вас недостаточно денег для покупки этого предмета." << endl;
    }
  } else {
    cout << "Неверный выбор." << endl;
  }
  return 0;
}

bool useItemByNumber(vector<catItem> &catInventory, int itemNumber,
                     Pet &myPet) {
  cout << "Инвентарь: " << endl;
  for (int i = 0; i < catInventory.size(); ++i) {
    if (catInventory[i].quan > 0) {
      cout << catInventory[i].name << " (" << catInventory[i].quan << ")"
           << endl;
    }
    if (catInventory[i].quan == 0) {
      cout << "Предмет " << catInventory[i].name << " удален из инвентаря"
           << endl;
      catInventory.erase(catInventory.begin() + i);
      --i;
    }
  }

  cout << "Введите номер предмета, который хотите использовать (от 0): ";
  cin >> itemNumber;

  if (itemNumber >= 0 && itemNumber < catInventory.size()) {
    string itemName = catInventory[itemNumber].name;
    bool itemFound = false;

    for (auto &item : catInventory) {
      if (item.name == itemName && item.quan > 0) {
        int effectMultiplier = 1;

        if (item.rarity == "\033[32mrare \033[0m ") {
          effectMultiplier = 2;
        } else if (item.rarity == "\033[35mepic \033[0m") {
          effectMultiplier = 4;
        } else if (item.rarity == "\033[36msuperrare \033[0m") {
          effectMultiplier = 3;
        } else if (item.rarity == "\033[33mlegendary \033[0m") {
          effectMultiplier = 5;
        }
        if (itemName == "царский кристраж" || itemName == "царский корм" ||
            itemName == "огромный кристалл") {
          myPet.health += item.effect * effectMultiplier;
          myPet.Maxhealth += item.effect * effectMultiplier;
          item.quan--;
        } else if (itemName == "большой кристалл" ||
                   itemName == "великая сфера" ||
                   itemName == "кристаллелалаж радости" ||
                   itemName == "большую сферу" ||
                   itemName == "кристалическая сфера") {
          myPet.atc += item.effect * effectMultiplier;
          myPet.Maxatc += item.effect * effectMultiplier;
          item.quan--;
        } else if (itemName == "Корм для питомца") {
          string choice;
          cout << "Покормить питомца? ";
          cin >> choice;
          if (choice == "да" || choice == "yes") {
            eatCat(myPet, catInventory);
            item.quan--;
          } else {
            cout << "Вы не покормили питомца" << endl;
          }
        }

        cout << "Вы использовали " << itemName << endl;
        itemFound = true;
        break;
      }
    }

    if (!itemFound) {
      cout << "У вас нет " << itemName << " в инвентаре." << endl;
    }
  } else {
    cout << "Неверный номер предмета." << endl;
  }

  return false;
}

int ring(vector<enemy> &enemies, Pet &myPet) {
  cout << "\x1B[2J\x1B[H";
  cout << "Вас пригласили на ринг" << endl;
  int x = rand() % enemies.size();
  enemy chosenEnemy = enemies[x];
  cout << "Ваш противник: " << chosenEnemy.name << endl;
  cout << "Здоровье противника: " << chosenEnemy.health << endl;
  cout << "Атака противника: " << chosenEnemy.atk << endl;
  cout << chosenEnemy.image << endl;
  while (chosenEnemy.health > 0 && myPet.health > 0) {
    cout << "1. Удар передней лапой" << endl;
    cout << "2. Удар задней лапой" << endl;
    cout << "3. Удар головой " << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
      chosenEnemy.health -= myPet.atc;
      break;
    case 2:
      chosenEnemy.health -= myPet.atc * 1.5;
      break;
    case 3:
      chosenEnemy.health -= myPet.atc * 2;
      myPet.health -= 10;
      break;
    default:
      cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
      break;
    }
    if (chosenEnemy.health > 0) {
      myPet.health -= chosenEnemy.atk;
      cout << "Противник атакует! Ваше здоровье: " << myPet.health << endl;
    }
  }
  if (myPet.health <= 0) {
    cout << "Вы проиграли." << endl;
    return -1;
  } else {
    cout << "Вы победили " << chosenEnemy.name << "!" << endl;
    myPet.money += 200;
    myPet.happiness += 250;
    myPet.xp += 150;
    return 0;
  }
}

bool itemExists(vector<catItem> &inventory, string itemName) {
  for (int i = 0; i < inventory.size(); ++i) {
    if (inventory[i].name == itemName) {
      return true;
    }
  }
  return false;
}

void deleteOneQuantityOfItem(vector<catItem> &inventory, string itemToDelete) {
  for (int i = 0; i < inventory.size(); ++i) {
    if (inventory[i].name == itemToDelete) {
      inventory[i].quan--;
    }
    if (inventory[i].quan == 0) {
      cout << "Предмет " << inventory[i].name
           << " удален полностью из инвентаря" << endl;
      inventory.erase(inventory.begin() + i);
    }
  }
}

int craftItems(vector<catItem> &inventory) {
  bool canCraft = false;
  if (itemExists(inventory, "большой кристалл") &&
      itemExists(inventory, "царский кристраж")) {
    cout << "Крафт 1. Есть возможность скрафтить кристаллелалаж радости, "
            "используя предметы большой кристалл и царский кристраж."
         << endl;
    canCraft = true;
  }
  if (itemExists(inventory, "Корм для питомца") &&
      itemExists(inventory, "царский кристраж")) {
    cout << "Крафт 2. Есть возможность скрафтить царский корм, используя "
            "предметы Корм для питомца и царский кристраж."
         << endl;
    canCraft = true;
  }
  if (itemExists(inventory, "великая сфера") &&
      itemExists(inventory, "большой кристалл")) {
    cout << "Крафт 3. Есть возможность скрафтить большую сферу, используя "
            "предметы великая сфера и большой кристалл."
         << endl;
    canCraft = true;
  }
  int countBigCrystal = 0;
  for (const auto &item : inventory) {
    if (item.name == "большой кристалл") {
      countBigCrystal++;
    }
  }
  if (countBigCrystal >= 2) {
    cout << "Крафт 4. Есть возможность скрафтить огромный кристалл, используя "
            "2 больших кристалла."
         << endl;
    canCraft = true;
  }
  if (itemExists(inventory, "великая сфера") &&
      itemExists(inventory, "большой кристалл") &&
      itemExists(inventory, "царский кристраж") &&
      itemExists(inventory, "царский кристраж")) {
    cout << "Крафт 5. Есть возможность скрафтить кристаллическую сферу, "
            "используя предметы великая сфера, 2 больших кристалла и царский "
            "кристраж."
         << endl;
    canCraft = true;
  }
  if (!canCraft) {
    cout << "У вас нет необходимых предметов для крафта." << endl;
    waitForEnter();
    return 0;
  }

  int choice;
  cout << "Выберите крафт: (или нажмите 6 для выхода)";
  cin >> choice;
  switch (choice) {
  case 1:
    if (itemExists(inventory, "большой кристалл") &&
        itemExists(inventory, "царский кристраж")) {
      deleteOneQuantityOfItem(inventory, "большой кристалл");
      deleteOneQuantityOfItem(inventory, "царский кристраж");
      inventory.push_back(
          {"кристаллелалаж радости", 1, 15, "\033[33mlegendary \033[0m"});
      cout << "Вы успешно скрафтили кристаллелалаж радости." << endl;
    } else {
      cout << "У вас нет необходимых предметов для скрафта." << endl;
      return 0;
    }
    break;
  case 2:
    if (itemExists(inventory, "Еда для питомца") &&
        itemExists(inventory, "царский кристраж")) {
      deleteOneQuantityOfItem(inventory, "Еда для питомца");
      deleteOneQuantityOfItem(inventory, "царский кристраж");
      inventory.push_back({"царский корм", 1, 7, "\033[35mepic \033[0m"});
      cout << "Вы успешно скрафтили царский корм." << endl;
    } else {
      cout << "У вас нет необходимых предметов для скрафта." << endl;
      return 0;
    }
    break;
  case 3:
    if (itemExists(inventory, "великая сфера") &&
        itemExists(inventory, "большой кристалл")) {
      deleteOneQuantityOfItem(inventory, "великая сфера");
      deleteOneQuantityOfItem(inventory, "большой кристалл");
      inventory.push_back(
          {"большая сфера", 1, 17, "\033[33mlegendary \033[0m"});
      cout << "Вы успешно скрафтили большую сферу." << endl;
    } else {
      cout << "У вас нет необходимых предметов для скрафта." << endl;
      return 0;
    }
    break;
  case 4:
    if (itemExists(inventory, "большой кристалл")) {
      deleteOneQuantityOfItem(inventory, "большой кристалл");
      deleteOneQuantityOfItem(inventory, "большой кристалл");
      inventory.push_back(
          {"огромный кристалл", 1, 30, "\033[33mlegendary \033[0m"});
      cout << "Вы успешно скрафтили огромный кристалл." << endl;
    } else {
      cout << "У вас нет необходимых предметов для скрафта." << endl;
      return 0;
    }
    break;
  case 5:
    if (itemExists(inventory, "великая сфера") &&
        itemExists(inventory, "большой кристалл") &&
        itemExists(inventory, "царский кристраж") &&
        itemExists(inventory, "царский кристраж")) {
      deleteOneQuantityOfItem(inventory, "великая сфера");
      deleteOneQuantityOfItem(inventory, "большой кристалл");
      deleteOneQuantityOfItem(inventory, "царский кристраж");
      deleteOneQuantityOfItem(inventory, "царский кристраж");
      inventory.push_back(
          {"кристаллическая сфера", 1, 40, "\033[33mlegendary \033[0m"});
      cout << "Вы успешно скрафтили кристаллическую сферу." << endl;
    } else {
      cout << "У вас нет необходимых предметов для скрафта." << endl;
      return 0;
    }
    break;
  default:
    cout << "Неверный выбор." << endl;
    return 0;
  }
  return 1;
}

void drawSercher() {
  for (int i = 0; i < 3; i++) {
    cout << "\n";

    cout << "\b\\" << endl;
    chrono::milliseconds search1(600);
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b|" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b/" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b-" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b\\" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b|" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";

    cout << endl;
    cout << "\b/" << endl;
    this_thread::sleep_for(search1);
    cout << "\x1B[2J\x1B[H";
  }
  for (int i = 0; i < 1; i++) {
    cout << "\x1B[2J\x1B[H";
    cout << "\n";
    cout << "\b-" << endl;
    chrono::milliseconds search2(1000);
    this_thread::sleep_for(search2);
    cout << "\x1B[2J\x1B[H";
  }
  for (int i = 0; i < 1; i++) {
    cout << "\x1B[2J\x1B[H";
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "\033[32m";
    cout << " ## ##     ##     ##   ##  ##  ###  ### ##     ##       ####      "
            "      ### ##   ### ###  #### ##  "
         << endl;
    chrono::milliseconds search(1000);
    this_thread::sleep_for(search);
    cout << "##   ##     ##     ## ##   ##   ##   ##  ##     ##       ##       "
            "       ##  ##   ##  ##  # ## ##  "
         << endl;
    cout << "####      ## ##   # ### #  ##   ##   ##  ##   ## ##      ##       "
            "       ##  ##   ##        ##     "
         << endl;
    this_thread::sleep_for(search);
    cout << " #####    ##  ##  ## # ##  ##   ##   ## ##    ##  ##     ##       "
            "       ##  ##   ## ##     ##     "
         << endl;
    this_thread::sleep_for(search);
    cout << "    ###   ## ###  ##   ##  ##   ##   ## ##    ## ###     ##       "
            "       ## ##    ##        ##     "
         << endl;
    this_thread::sleep_for(search);
    cout << "##   ##   ##  ##  ##   ##  ##   ##   ##  ##   ##  ##     ##       "
            "       ##       ##  ##    ##     "
         << endl;
    this_thread::sleep_for(search);
    cout << " ## ##   ###  ##  ##   ##   ## ##   #### ##  ###  ##    ####      "
            "      ####     ### ###   ####    "
        "\033[0m"<< endl;
    
    this_thread::sleep_for(search);
    cout << "\x1B[2J\x1B[H";
    this_thread::sleep_for(search);
  }
}

int main() {

  setlocale(LC_ALL, "Russian");

  cout << "\x1B[2J\x1B[H";
  Pet myPet;
  myPet.level = 0;
  myPet.health = 100;
  myPet.happiness = 100;
  myPet.xp = 0;
  myPet.Maxhealth = 100;
  myPet.money = 100;
  myPet.atc = 10;
  myPet.Maxatc = 10;
  dog dogbattle;
  dogbattle.health = 50;
  dogbattle.atc = 5;
  dogbattle.BOSatc = 10;
  dogbattle.BOShealth = 100;
  vector<ShopItem> shopItems = {
      {"Еда для питомца", 10, 5, "\033[32mrare \033[0m "},
      {"великая сфера", 50, 5, "\033[35mepic \033[0m"},
      {"царский кристраж", 50, 3, "\033[36msuperrare \033[0m"},
      {"большой кристалл", 100, 11, "\033[33mlegendary \033[0m"},
      {"кристаллелалаж радости", 250, 15, "\033[33mlegendary \033[0m"},
      {"царский корм", 70, 7, "\033[35mepic \033[0m"},
      {"большую сферу", 270, 17, "\033[33mlegendary \033[0m"},
      {"огромный кристалл", 400, 30, "\033[33mlegendary \033[0m"},
      {"кристалическая сфера", 500, 50, "\033[33mlegendary \033[0m"},
  };
  vector<catItem> inventory;
  vector<enemy> enemy = {
      {"Злосный кот", 200, 15,
       " |\\_---_/|\n /   o_o   \\\n |    U    |\n \\ ._I_.  /\n  "
       "`-_____-},\n"},
      {"Пират", 134, 16,
       "_ |\\_\n \\` ..\\\n __,.-  =__Y=\n /        )\n /   ,    \\/\\_\n "
       "((____|    )_-\\ \\_-`\n `-----'`-----` `--`"},
      {"Император", 145, 11},
      {"Чертила", 300, 6},
  };
  drawSercher();
  cout << "Введите имя вашего питомца: ";
  getline(cin, myPet.name);
  bool isRunning = true;
  while (isRunning) {
    displayPet(myPet, inventory);
    if (myPet.health <= 0) {
      cout << "\x1B[2J\x1B[H";
      cout << "Питомец умер. Игра окончена." << endl;
      cout << "              __" << endl;
      cout << "             /(X" << endl;
      cout << "       ,-,  //  \\\\" << endl;
      cout << "      (,X,) ||   v" << endl;
      cout << "     (,X,,)\\X/" << endl;
      cout << "     (X,,/w)-'" << endl;
      cout << "     \\,Xw)" << endl;
      cout << "     v/Xu" << endl;
      cout << "       / |" << endl;
      cout << "       | X" << endl;
      cout << "       X o" << endl;
      cout << "       \\ X" << endl;
      cout << "        \\|" << endl;
      isRunning = false;
    } else {
      displayMenu();
      int choice;
      cout << "Выберите действие: ";
      cin >> choice;
      switch (choice) {
      case 1:
        cout << "\x1B[2J\x1B[H";
        playCat(myPet);
        break;
      case 2:
        cout << "\x1B[2J\x1B[H";
        eatCat(myPet, inventory);
        break;
      case 3:
        cout << "\x1B[2J\x1B[H";
        travlCat(myPet, dogbattle);
        break;
      case 4:
        cout << "\x1B[2J\x1B[H";
        rangCat(myPet, dogbattle, enemy);
        break;
      case 5:
        cout << "\x1B[2J\x1B[H";
        shop(myPet, shopItems, inventory);
        break;
      case 6:
        cout << "\x1B[2J\x1B[H";
        useItemByNumber(inventory, 0, myPet);
        break;
      case 7:
        cout << "\x1B[2J\x1B[H";
        ring(enemy, myPet);
        break;
      case 8:
        cout << "\x1B[2J\x1B[H";
        craftItems(inventory);
      default:
        cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
      }
    }
  }
  return 0;
}