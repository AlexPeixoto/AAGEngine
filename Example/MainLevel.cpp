//
//  MainLevel.cpp
//  AAGEngine
//
//  Created by Alex Peixoto on 7/2/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#include "MainLevel.h"
using Core::Collision;
using Core::Node;
using Core::Pathfind;
using Core::InputControl;

MainLevel::MainLevel():Level(){
    spaceIsPressed=cIsPressed=returnIsPressed=false;
    renderText=true;
    textIndex=0;
    isthread=false;
    p=new Adventure::Player("/Developer/movement.png", 32, 64);
    t=new Core::TextControl("/Developer/times.ttf");
    sl=new ScreenLog("/Developer/times.ttf");
    bs=new Core::BackgroundShape();
    d=new Dialog("/Developer/times.ttf");
    mapLevel="/Users/alexpeixoto/Desktop/m7.map";
    collisionLevel="/Users/alexpeixoto/Desktop/m7.map.collision";
    itemLevel="/Users/alexpeixoto/Desktop/m7.map.item";
    soundLevel="/Users/alexpeixoto/Desktop/m7.map.sound";
    objectLevel="/Users/alexpeixoto/Desktop/m7.map.object";
    warpLevel="/Users/alexpeixoto/Desktop/m7.map.warp";
    mapManager.loadTileLayer(mapLevel);
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadSoundMap(soundLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    initData();
}

MainLevel::MainLevel(map<string, string> params):Level(){
    isthread=true;
    spaceIsPressed=cIsPressed=returnIsPressed=false;
    renderText=true;
    textIndex=0;
    p=new Adventure::Player(params.find("player")->second, 32, 64);
    t=new Core::TextControl(params.find("font")->second);
    sl=new ScreenLog(params.find("font")->second);
    bs=new Core::BackgroundShape();
    d=new Dialog(params.find("font")->second);
    mapLevel=params.find("mapLevel")->second;//"/Users/alexpeixoto/Desktop/m7.map";
    collisionLevel=params.find("mapCollision")->second;//"/Users/alexpeixoto/Desktop/m7.map.collision";
    itemLevel=params.find("mapItem")->second;//"/Users/alexpeixoto/Desktop/m7.map.item";
    soundLevel=params.find("mapSound")->second;//"/Users/alexpeixoto/Desktop/m7.map.sound";
    objectLevel=params.find("mapObject")->second;//"/Users/alexpeixoto/Desktop/m7.map.object";
    warpLevel=params.find("mapWarp")->second;;
    mapManager.loadTileLayer(mapLevel);
    mapManager.loadCollisionMap(collisionLevel);
    mapManager.loadItemMap(itemLevel);
    mapManager.loadSoundMap(soundLevel);
    mapManager.loadObjectMap(objectLevel);
    mapManager.loadWarpMap(warpLevel);
    initData();
}

void MainLevel::initData(){
    
    
    //OBB TEST
    i1=new Core::Image("/Users/alexpeixoto/Desktop/b1.png");
    i2=new Core::Image("/Users/alexpeixoto/Desktop/b2.png");
    i1->setPosition(Point2i(0, 0));
    i2->setPosition(Point2i(100, 0));
    
    TextTable::loadFromFile("/Users/alexpeixoto/Desktop/gametext.txt");
    /*for(const auto kv : TextTable::getAllKeyValues()){
        cout << kv.first << "-" << kv.second << endl;
    }
    exit(0);*/
    //Dialog shapes
    speechBox=new Core::BackgroundShape();
    questionBox=new Core::BackgroundShape();;
    optionShape=new Core::BackgroundShape();
    speechBox->setBorderSize(1);
    questionBox->setBorderSize(1);
    optionShape->setBorderSize(1);
    
    speechBox->setBorderColor(10, 10, 10, 255);
    questionBox->setBorderColor(10, 10, 10, 255);
    optionShape->setBorderColor(20, 20, 20, 255);
    
    speechBox->setInsideColor(30, 30, 30, 120);
    questionBox->setInsideColor(30, 30, 30, 255);
    optionShape->setInsideColor(200, 40, 40, 255);
    
    _m = new Menu("/Developer/times.ttf");
    
    _p=new Adventure::Character("/Developer/movement.png", 32, 64);
    _p->setPosition(Point2f(0, 15));
    _p->setChangeOnCall(20);
    _p->setLoop(true);
    _p->resetLoopTo(3);
    generatePathForPlayer();
    _p->moveWithNodes(pfBeginNode, mapManager.getMovementPointer(), Vector2i(30, 30), Vector2i(15, 15), 60);
    
    Point2f playerPosition;
    playerPosition.x = 100;//Game::window->getPosition().x / 2;
    playerPosition.y = 100;//Game::window->getPosition().y / 2;
    p->setPosition(playerPosition);
    p->setLoop(true);
    p->setPixelsPerCall(100);
    p->resetLoopTo(3);
    p->setWidthScale(1);
    p->setHeightScale(1);
    p->setChangeOnCall(20);
    Core::Image::setWindow(Game::window);
    Core::TextControl::setWindow(Game::window);
    t->setSpacing(5);
    t->setText("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85 86 87 88 89 90 91 92 93 94 95 96 97 98 99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 115 116 117 118 119 120 121 122 123 124 125 126 127 128 129 130 131 132 133 134 135 136 137 138 139 140 141 142 143 144 145 146 147 148 149 150 151 152 153 154 155 156 157 158 159 160 161 162 163 164 165 166 167 168 169 170 171 172 173 174 175 176 177 178 179 180 181 182 183 184 185 186 187 188 189 190 191 192 193 194 195 196 197 198 199 200 201 202 203 204 205 206 207 208 209 210 211 212 213 214 215 216 217 218 219 220 221 222 223 224 225 226 227 228 229 230 231 232 233 234 235 236 237 238 239 240 241 242 243 244 245 246 247 248 249 250 251 252 253 254 255 256 257 258 259 260 261 262 263 264 265 266 267 268 269 270 271 272 273 274 275 276 277 278 279 280 281 282 283 284 285 286 287 288 289 290 291 292 293 294 295 296 297 298 299 300 301 302 303 304 305 306 307 308 309 310 311 312 313 314 315 316 317 318 319 320 321 322 323 324 325 326 327 328 329 330 331 332 333 334 335 336 337 338 339 340 341 342 343 344 345 346 347 348 349 350 351 352 353 354 355 356 357 358 359 360 361 362 363 364 365 366 367 368 369 370 371 372 373 374 375 376 377 378 379 380 381 382 383 384 385 386 387 388 389 390 391 392 393 394 395 396 397 398 399 400 401 402 403 404 405 406 407 408 409 410 411 412 413 414 415 416 417 418 419 420 421 422 423 424 425 426 427 428 429 430 431 432 433 434 435 436 437 438 439 440 441 442 443 444 445 446 447 448 449 450 451 452 453 454 455 456 457 458 459 460 461 462 463 464 465 466 467 468 469 470 471 472 473 474 475 476 477 478 479 480 481 482 483 484 485 486 487 488 489 490 491 492 493 494 495 496 497 498 499 500 501 502 503 504 505 506 507 508 509 510 511 512 513 514 515 516 517 518 519 520 521 522 523 524 525 526 527 528 529 530 531 532 533 534 535 536 537 538 539 540 541 542 543 544 545 546 547 548 549 550 551 552 553 554 555 556 557 558 559 560 561 562 563 564 565 566 567 568 569 570 571 572 573 574 575 576 577 578 579 580 581 582 583 584 585 586 587 588 589 590 591 592 593 594 595 596 597 598 599 600 601 602 603 604 605 606 607 608 609 610 611 612 613 614 615 616 617 618 619 620 621 622 623 624 625 626 627 628 629 630 631 632 633 634 635 636 637 638 639 640 641 642 643 644 645 646 647 648 649 650 651 652 653 654 655 656 657 658 659 660 661 662 663 664 665 666 667 668 669 670 671 672 673 674 675 676 677 678 679 680 681 682 683 684 685 686 687 688 689 690 691 692 693 694 695 696 697 698 699 700 701 702 703 704 705 706 707 708 709 710 711 712 713 714 715 716 717 718 719 720 721 722 723 724 725 726 727 728 729 730 731 732 733 734 735 736 737 738 739 740 741 742 743 744 745 746 747 748 749 750 751 752 753 754 755 756 757 758 759 760 761 762 763 764 765 766 767 768 769 770 771 772 773 774 775 776 777 778 779 780 781 782 783 784 785 786 787 788 789 790 791 792 793 794 795 796 797 798 799 800 801 802 803 804 805 806 807 808 809 810 811 812 813 814 815 816 817 818 819 820 821 822 823 824 825 826 827 828 829 830 831 832 833 834 835 836 837 838 839 840 841 842 843 844 845 846 847 848 849 850 851 852 853 854 855 856 857 858 859 860 861 862 863 864 865 866 867 868 869 870 871 872 873 874 875 876 877 878 879 880 881 882 883 884 885 886 887 888 889 890 891 892 893 894 895 896 897 898 899 900 901 902 903 904 905 906 907 908 909 910 911 912 913 914 915 916 917 918 919 920 921 922 923 924 925 926 927 928 929 930 931 932 933 934 935 936 937 938 939 940 941 942 943 944 945 946 947 948 949 950 951 952 953 954 955 956 957 958 959 960 961 962 963 964 965 966 967 968 969 970 971 972 973 974 975 976 977 978 979 980 981 982 983 984 985 986 987 988 989 990 991 992 993 994 995 996 997 998 999 1000");
    t->setColor(255, 255, 255, 255);
    t->setScale(.5);
    t->splitInScreens(300, 100);
    
    
    //Handles the text when some event happens.
    messagePending=false;
    message="";
    
    //BackgroundMusic::loadSong("/Users/alexpeixoto/Downloads/AF/S0.ogg");
    //BackgroundMusic::play();
    //BackgroundMusic::intersectWith("/Users/alexpeixoto/Downloads/AF/S2.ogg", BackgroundMusic::IntersectMode::CROSS, 10);
    
    Debug::LogManager::addLevelDestiny(Debug::LogLevel::WARNING, Debug::Destiny::Console);
    mapManager.getSoundMap()->playAll();
    sl->setPosition(Point2i(Game::window->getSize().x-250, 0));
    sl->setSize(Vector2i(250, 100));
    sl->setSpacing(5);
    sl->setScale(.5);
    LogManager::addLevelDestiny(Debug::LogLevel::MESSAGE, Debug::Destiny::Screen, sl);
    LogManager::addLevelDestiny(Debug::LogLevel::WARNING, Debug::Destiny::Console, sl);
    LogManager::addLevelDestiny(Debug::LogLevel::ERROR, Debug::Destiny::File, "/Developer/file.text", false);
    LogManager::log(Debug::LogLevel::ERROR, "Test", "");
    LogManager::removeLevelDestiny(Debug::LogLevel::ERROR, Debug::Destiny::File);
    
    bs->setBorderSize(2);
    bs->setBorderColor(10, 100, 10, 255);
    bs->setInsideColor(100, 100, 0, 180);
    bs->setSize(Vector2i(260, 110));
    bs->setPosition(Point2i(Game::window->getSize().x-262, 2));
    
    d->setSpeechColor(255, 255, 255, 255);
    d->setDialogBoxSize(Vector2i(Game::window->getSize().x, 200));
    d->setDialogBoxPosition(Point2i(0, Game::window->getSize().y-202));
    d->setSpeechBoxShape(speechBox);
    
    d->setQuestionColor(255, 255, 255, 255);
    d->setQuestionBoxSize(Vector2i(150, 100));
    d->setQuestionBoxPosition(Point2i(0, Game::window->getSize().y-400));
    d->setQuestionBoxShape(questionBox);
    
    d->setQuestionBoxByLargest(true);
    
    d->setOptionInnerBorder(5);
    d->setOptionShape(optionShape);
    
    d->addSpeech(0, TextTable::getByKey("WYW"), false);
    d->addSpeech(1, TextTable::getByKey("OO"), true);
    d->addSpeech(2, TextTable::getByKey("N"), true);
    
    
    d->addQuestion(0, "Do you like cheese?", [](int speechId, int questionId, int optionId, Dialog* dialog) -> void {
        dialog->setRenderingQuestion(false);
        if(speechId==0 && questionId==0 && optionId==0)
            dialog->gotoSpeech(1);
        else if(speechId==0 && questionId==0 && optionId==1)
            dialog->gotoSpeech(2);
    });
    
    d->addOption(0, 0, "No, i hate that1");
    d->addOption(0, 1, "A lot");
    d->addOption(0, 2, "No, i hate that2");
    d->addOption(0, 3, "A lot");
    d->addOption(0, 4, "No, i hate that3");
    d->addOption(0, 5, "A lot");
    d->addOption(0, 6, "No, i hate that4");
    d->addOption(0, 7, "A lot");
    d->addOption(0, 8, "No, i hate that5");
    d->addOption(0, 9, "A lot");
    d->addOption(0, 10, "No, i hate that6");
    d->addOption(0, 11, "A lot");
    d->addOption(0, 12, "No, i hate that7");
    d->addOption(0, 13, "A lot");
    
    //On the Speech 0 i have the question 0
    d->addDialogHandle(0, 0);
    
    mapManager.getSoundMap()->getSounds()->at(0)->sound->setVolume(10000);
}
void MainLevel::generatePathForPlayer(){
    pf=new Pathfind();
    int limit=50*50;
    int* map=new int[limit];
    int* movementMap=new int[limit];

    for(int x=0;x<limit;x++){
        map[x]=0;
        movementMap[x]=0;
    }
    pf->initMatrix(Vector2i(50, 50), movementMap);
    pfBeginNode=pf->generatePathfind(Point2i(0, 1), Point2i(10, 10), 1);
}
void MainLevel::getItem(){
    //Player bounding box and item bounding box
    Core::Collision::BoundingBox b, ibb;
    
    
    b.size.x=this->p->getSprite()->getTileSize().x;
    b.size.y=ceil(this->p->getSprite()->getTileSize().y/2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    //get an
    b.position-=(Point2f)mapManager.getMovement();
    auto* itemList=mapManager.getItemMap()->getItemList();
    for(int x=0; x<itemList->size(); x++){
        ibb=mapManager.getItemMap()->getBoundingBox(itemList->at(x));
        if(Collision::collidedAABB(ibb, b)){
            message="You got an " + ItemManager::getItem(itemList->at(x)->id)->getName();
            messagePending=true;
            itemList->erase(itemList->begin()+x);
            x=0;
            LogManager::log(Debug::LogLevel::MESSAGE, "%T", message);
            
        }
    }
}
void MainLevel::showMessage(){
    if(messagePending){
        //Get just one letter height
        t->renderSimpleText( p->getPosition().x - t->getWidth(message)/2, p->getPosition().y - t->getHeight("A"),  message);
    }
}
void MainLevel::movement(){
    Core::Collision::BoundingBox b;
    
    b.size.x=this->p->getSprite()->getTileSize().x;
    b.size.y=ceil(this->p->getSprite()->getTileSize().y/2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::LShift, Core::InputControl::State::Held)){
        this->p->setPixelsPerCall(200);
        this->p->setChangeOnCall(18);
    }
    else{
        this->p->setChangeOnCall(25);
        this->p->setPixelsPerCall(100);
    }
    
    if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Right, Core::InputControl::State::Held)){
        //Check if the player can move
        //I need to get the float position from the player and add the movement to check if it is allowed
        b.position.x=this->p->getPosition().x+this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::RIGHT, true);
            this->p->setSpriteColumn(1);
            return;
        }

        
        //Move Player
        else if(this->p->getPosition().x < Game::window->sf::Window::getSize().x - Game::window->getSize().x*.2f){
            this->p->updateByKeyboard(Adventure::Character::Directions::RIGHT, Game::getDeltaTimef());
        }
        //Move Camera
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(-this->p->getPixelsPerCall()*Game::getDeltaTimef(), 0);
            this->p->updateDirection(Adventure::Character::Directions::RIGHT, true);
            this->p->call();
        }
    }
    
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Left, Core::InputControl::State::Held)){
        b.position.x=this->p->getPosition().x-this->p->getPixelsPerCall()*Game::getDeltaTimef();
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.x < 0){
            this->p->updateDirection(Adventure::Character::Directions::LEFT, true);
            this->p->setSpriteColumn(1);
            return;
        }
        
        else if(this->p->getPosition().x >  Game::window->getSize().x*.2f || -this->mapManager.getMovement().x < 0)
            this->p->updateByKeyboard(Adventure::Character::Directions::LEFT, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(this->p->getPixelsPerCall()*Game::getDeltaTimef(), 0);
            this->p->updateDirection(Adventure::Character::Directions::LEFT, true);
            this->p->call();
        }
        
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Up, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y-this->p->getPixelsPerCall()*Game::getDeltaTimef()+b.size.y;
        
        if(this->mapManager.collided(b) || -this->mapManager.getMovement().x + b.position.y < 0){
            this->p->updateDirection(Adventure::Character::Directions::UP, true);
            this->p->setSpriteColumn(1);
            return;
        }
        else if(this->p->getPosition().y >  Game::window->getSize().y*.2f || -this->mapManager.getMovement().y < 0)
            this->p->updateByKeyboard(Adventure::Character::Directions::UP, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(0, this->p->getPixelsPerCall()*Game::getDeltaTimef());
            this->p->updateDirection(Adventure::Character::Directions::UP, true);
            this->p->call();
        }
    }
    else if(Core::InputControl::getKeyboardKeyStatus(Keyboard::Down, Core::InputControl::State::Held)){
        b.position.y=this->p->getPosition().y+(this->p->getPixelsPerCall()*Game::getDeltaTimef())+b.size.y;
        
        if(this->mapManager.collided(b)){
            this->p->updateDirection(Adventure::Character::Directions::DOWN, true);
            this->p->setSpriteColumn(1);
            return;
        }
        else if(this->p->getPosition().y + b.size.y*2 <  Game::window->sf::Window::getSize().y - Game::window->getSize().y*.2f)
            this->p->updateByKeyboard(Adventure::Character::Directions::DOWN, Game::getDeltaTimef());
        else{
            //get movement too, crete this->p->getMovement(Adventure::Prototype::Directions::RIGHT);
            this->mapManager.move(0, -this->p->getPixelsPerCall()*Game::getDeltaTimef());
            this->p->updateDirection(Adventure::Character::Directions::DOWN, true);
            this->p->call();
        }
    }
}
void MainLevel::openObject(){
    int threshhold=10;
    Core::Collision::BoundingBox b;
    
    b.size.x=this->p->getSprite()->getTileSize().x;
    b.size.y=ceil(this->p->getSprite()->getTileSize().y/2);
    b.position.x=this->p->getPosition().x;
    b.position.y=this->p->getPosition().y+b.size.y;
    int index;
    if(p->getFacing()==Character::Directions::UP){
        //Goes UP on the map, then it can intersect with object
        b.position.y-=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            mapManager.getObjectMap()->setSpriteIndex(index, 0, 4);
        }
    }
    if(p->getFacing()==Character::Directions::DOWN){
        //Goes UP on the map, then it can intersect with object
        b.position.y+=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            mapManager.getObjectMap()->setSpriteIndex(index, 0, 4);
        }
    }
    if(p->getFacing()==Character::Directions::LEFT){
        //Goes UP on the map, then it can intersect with object
        b.position.x-=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            mapManager.getObjectMap()->setSpriteIndex(index, 0, 4);
        }
    }
    if(p->getFacing()==Character::Directions::RIGHT){
        //Goes UP on the map, then it can intersect with object
        b.position.x+=threshhold;
        if(((index=mapManager.getObjectMap()->collidedWith(b, mapManager.getMovement())) >= 0)){
            mapManager.getObjectMap()->setSpriteIndex(index, 0, 4);
        }
    }
}
void MainLevel::changeIndex(){
    //Change text index
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Space, Core::InputControl::State::Released)){
        spaceIsPressed=true;
    }
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Space, Core::InputControl::State::Released)){
        spaceIsPressed=false;
        messagePending=false;
        message="";
        if(textIndex==t->numberOfScreens()-1){
            textIndex=0;
        }
        textIndex++;
    }
}
void MainLevel::process(){
    Game::setDeltaTime();
    
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::C, Core::InputControl::State::Released)){
        cIsPressed=true;
    }
    if(cIsPressed && !Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::C, Core::InputControl::State::Released) && !d->getRenderingQuestion()){
        if(d->haveQuestion()){
            d->setRenderingQuestion(true);
            cIsPressed=false;
        }
        else if(renderText){
            cIsPressed=false;
            if(d->nextSpeech()==false)
                renderText=false;
        }
        else if(cIsPressed && !Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::C, Core::InputControl::State::Released)){
            cIsPressed=false;
            openObject();
        }
    }
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::G, Core::InputControl::State::Released)){
        i1->setRotation(i1->getRotation()+.5f);
    }
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::D, Core::InputControl::State::Released)){
        i1->setPosition(Point2i(i1->getPosition().x+1, i1->getPosition().y));
        Point2f a1[4];
        Point2f a2[4];
        Collision::getImageAxis(i1, a1);
        Collision::getImageAxis(i2, a2);
        if(Collision::collidedOBB(a1, a2) == true){
            cout << "Collided" << endl;
        }
        
    }
    if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::S, Core::InputControl::State::Released))
        i1->setPosition(Point2i(i1->getPosition().x-5, i1->getPosition().y));
    
/*    if(messagePending){
        changeIndex();
        return;
    }*/
    
    getItem();
    if(!d->getRenderingQuestion()){
        movement();
    }
    else{
        if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Up, Core::InputControl::State::Released))
            d->prevOption();
        else if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Down, Core::InputControl::State::Released))
            d->nextOption();
        else if(Core::InputControl::getKeyboardKeyStatus(Core::InputControl::KeyboardKey::Return, Core::InputControl::State::Released))
            d->selectOption();
            
    }
    mapManager.process(p->getPosition().x, p->getPosition().y, 0, 0);
}
void MainLevel::render(){
    mapManager.render(0, 0, Game::window->getSize().x, Game::window->getSize().y);
    p->render();
    showMessage();
    bs->render();
    sl->render();
    _p->render((Vector2i)mapManager.getMovement());
    //i1->render();
    //i2->render();
    if(renderText){
        d->renderSpeech();
        if(d->getRenderingQuestion())
            d->renderQuestion();
    }
}