//
//  LogManager.h
//  AAGEngine
//
//  Created by Alex Peixoto on 3/7/14.
//  Copyright (c) 2014 Alex Peixoto. All rights reserved.
//

#ifndef __Action_Adventure_Game_Engine__LogManager__
#define __Action_Adventure_Game_Engine__LogManager__

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <thread>
#include "ScreenLog.h"

namespace Debug {
    //! Enumerador que define niveis para mensagens.
    /*! A utilização dos niveis é de responsabilidade do desenvolvedor.
        O mesmo deve definir quando utilizar cada nivel.
    */
	enum class  LogLevel{
        ERROR, /*!< Mensagens de erro. */
        WARNING, /*!< Mensagens de alerta. */
        MESSAGE, /*!< Mensagens gerais, normalmente utilizadas para propositos de debug. */
        UNKNOWN /*!< Mensagems de de origem desconhecidas, normalmente utilizadas em exceptions */
    };
    //! Enumerador que define o destino de cada mensagaem.
    /*
        É possivel definir mais de um destino para uma mensagem.
        A Engine verifica se destinos para arquivos/dispositivos ja estão abertos.
        O LogManager não faz distinção entre Devide e File, os dois internamente funcionam da mesma maneira, os dois existem somente por questões de organização interna.
     */
    enum class Destiny{
#ifndef _WIN32
        Device, /*!< Mapeia dispositivos como destino, sendo unidades existentes no /dev/  (*nix/Mac Os X) */
#endif
        File, /*!< Mapeia arquivos como destino */
        Screen, /*! < Define uma ScreenLog como destino */
        Console /*!< Utiliza a saida padrão como destino (stdout) */
    };
    
    //! Classe responsável pela criação de logs.
    /*!
        Exemplo de utilização: <br />
            Debug::LogManager::addLevelDirection(Debug::LogLevel::WARNING, Debug::Destiny::Console); <br />
            string message = "test"; <br />
            int valor = 10; <br />
            LogManager::log(Debug::LogLevel::MESSAGE, "%T, com o valor %T", message, valor); <br />
     */
    class LogManager{
        
    private:
        /*! 
         Guarda um todos os mapeamentos existentes entre um LogLevel e um Destiny.
         É utilizado um vector<pair<..., ...>> pois é possivel existir multiplos destinos para o mesmo LogLevel
         */
        static std::vector<std::pair<LogLevel, Destiny>> *ld;
        
        //! Guarda lista de arquivos abertos
        static std::map<LogLevel, std::ofstream*> *fileOpenPool;
        //! Guarda lista de dispositivos abertos
        static std::map<LogLevel, std::ofstream*> *devOpenPool;
        //! Guarda lista de ScreenLog`s associadas ao LogLevel
        static std::map<LogLevel, ScreenLog*> *screenOpenPool;
        //! Define o Destiny::Console como /dev/stdout
        static std::ofstream* _stdout;
        //! Lista de niveis para utilizar como cabeçalho da mensagem
        static std::string levelPre[];

        
       //! Define template a ser chamado pelo <i> Variadic Template </i> log
        /*!
         Define metodo que recebe somente um parametro por template
         Este metodo é chamado pelo <i> log(O output, const char *s, T value, Args... args) </i>
         \param output define a saida (Device)
         \param string define a formatação da mensagem, sendo %T para qualquer parametro passado
         \param value recebe um dos parametros passados para o <i> Variadic Template </i>
         */
       template<typename O, typename T>
        static void log(O output, const char *string, T value){
            while(*string){
                if(*string == '%' && *(++string) == 'T'){
                    (*output)  << value;
                    ++string;
                    return;
                }
                (*output) << *(string++);
            }
            output->flush();
        }
        //! Define template que recebe lista de argumentos por <i> Variadic Template </i>.
        /*!
         Define metodo que recebe todos os parametros (args...), porem ao contrario da metodo log principal ele ja recebe o destino como um "ofstream".
         Para cada um dos args o metodo <i> log(O output, const char *s, T value) </i> é chamado
         \param output define a saida (Device)
         \param string define a formatação da mensagem, sendo %T para qualquer parametro passado
         \param value recebe um dos parametros passados para o <i> Variadic Template </i>
         \param args recebe a lista de parametros restantes, removendo o value (args...)
         */
        //When i have more than one argument the typename... (variadic template) is used
        template<typename O, typename T, typename... Args>
        static void log(O output, const char *string, T value, Args... args){
            while(*string){
                if(*string == '%' && *(++string) == 'T'){
                    //print the actual template value
                    (*output) << value;
                    ++string;
                    //get the remaining args with args... (removing the first element
                    log(output, string, args...);
                    return;
                }
                (*output) << *(string++);
            }
            output->flush();
        }

    public:
        //! Define metodo para relacionar um nivel de log com arquivos, dispositivos e console
        /*!
         Relaciona um nivel de log (LogLevel) com um destino (Destiny). <br />
         É verificado se o nivel não foi adicionado anteriormente para o destino informado, se sim a função termina sem nenhum retorno.
         \param logLevel define o nivel de log.
         \param destiny define o destino para se relacionar com a log.
         \param destinyFile define o arquivo de destino ou despositivo de destino.
         \param isDevice define se o destinyFile deve ser tratado como um dispositivo.
         */
        static void addLevelDestiny(LogLevel logLevel, Destiny destiny, const std::string& destinyFile="", bool isDevice=false);
        //! Define metodo para relacionar um nivel de log com um screenLog
        /*!
         Relaciona um nivel de log (LogLevel) com um destino (Destiny). <br />
         É verificado se o nivel não foi adicionado anteriormente para o destino informado, se sim a função termina sem nenhum retorno.
         \param logLevel define o nivel de log.
         \param destiny define o destino para se relacionar com a log.
         \param screen define o arquivo de destino ou despositivo de destino.
         */
        static void addLevelDestiny(LogLevel logLevel, Destiny destiny, ScreenLog *screen);
        //! Define metodo para remover uma associação entre nivel e destino
        /*!
         Remove a associação entre nivel e destino, desta forma se o nivel estiver varias associações com um mesmo destino todas são removidas. <br />
         Todos os file descriptors tanto de arquivos como de dispositivos são corretamente fechados e seus ponteiros deletados.
         \param logLevel define o nivel de log.
         \param destiny define o destino para se remover a associação
         */
        static void removeLevelDestiny(LogLevel logLevel, Destiny destiny);
        
        //!Define metodo a ser utilizado quando somente existe um argumento
        template<typename T>
        static void log(LogLevel logLevel, const char *string, T value){
            log(logLevel, string, value, "");
        }
        
        //! Define metodo principal de logs
        /*!
         Escreve o texto para todos os dispositivos, arquivos, telas e consoles mapeadas para o LogLevel.
         \param logLevel define para qual log deve ir a mensagem
         \param string define a string de formatação, exemplo: "Mensagem: %T no dia %T
         \param value primeiro valor a ser passado pelo variadic template
         \param args Outros valores a serem passados pelo variadic template, podendo ser 0 ou mais.
         */
        template<typename T, typename... Args>
        static void log(LogLevel logLevel, const char *string, T value, Args... args){
		
            #ifdef NODEBUG
                return;
            #endif
					if (ld == nullptr)
						return;
					if (_stdout == nullptr){
						_stdout = new std::ofstream();
						_stdout->open("/dev/stdout");
					}
					//For each device mapped to that LogLevel
					//I store the begin of the message
					const char *beginS = string;
					//The temporary ofstream
					std::ofstream* tmpof;
					//Loop throught the output
					for (auto &_ld : *ld){
						tmpof = nullptr;
						//Restart the s pointer
						string = beginS;

						//If not the LogLevel i wanted
						if (_ld.first != logLevel)
							continue;

						if (_ld.second == Destiny::Console){
							//ofstream devOut=ofstream();
							//devOut.open("/dev/stdout");
							tmpof = _stdout;
							(*tmpof) << levelPre[(int)logLevel] << std::endl;
							while (*string){
								if (*string == '%' && *(++string) == 'T'){
									(*tmpof) << value;
									++string;
									log(tmpof, string, args...);
									break;
								}
								(*tmpof) << *(string++);
							}
							(*tmpof) << std::endl;
							//Force to flush the data, if not the ofstream dont flush to /dev/stdout
							tmpof->flush();
						}
						else if (_ld.second == Destiny::Screen){
							for (auto it = screenOpenPool->begin(); it != screenOpenPool->end(); it++){
								ScreenLog* tmps = (*it).second;
								//Here i dont break line because the ScreenLog can delete the level information
								(*tmps) << levelPre[(int)logLevel];// << endl;
								(*tmps) << ":";
								while (*string){
									if (*string == '%' && *(++string) == 'T'){
										 (*tmps) << value;
										++string;
										log(tmps, string, args...);
										tmps->splitInScreens();
										break;
									}
									 (*tmps) << *(string++);
								}
								(*tmps) << '\n';
								tmps->splitInScreens();
							}
						}
						//Here i have to loop on the devices
						else{
							//I create an iterator so i can load everything on the file pool or on the device pool.
							//Now for each one of those i store the message inside the ofstream.
							std::map<LogLevel, std::ofstream*>::iterator bit, eit;
							if (_ld.second == Destiny::File){
								bit = fileOpenPool->begin();
								eit = fileOpenPool->end();
							}
#ifndef _WIN32
							else if(_ld.second==Destiny::Device){
								bit=devOpenPool->begin();
								eit=devOpenPool->end();
							}
#endif
							for (auto it = bit; it != eit; it++){
								tmpof = (*it).second;
								(*tmpof) << levelPre[(int)logLevel] << std::endl;
								while (*string){
									if (*string == '%' && *(++string) == 'T'){
										(*tmpof) << value;
										++string;
										log(tmpof, string, args...);
										break;
									}
									(*tmpof) << *(string++);
								}
								(*tmpof) << std::endl;
								//Force to flush the data, if not the ofstream dont flush to /dev/stdout
								tmpof->flush();
							}
						}
					}
        }
    };
}
#endif /* defined(__Action_Adventure_Game_Engine__LogManager__) */
