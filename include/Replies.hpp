#ifndef REPLIES_HPP
# define REPLIES_HPP

// ==================== REPLIES ====================

// Registro inicial del cliente
# define RPL_WELCOME        "001" // Bienvenida al cliente
# define RPL_YOURHOST       "002" // Información sobre el servidor
# define RPL_CREATED        "003" // Fecha de creación del servidor
# define RPL_MYINFO         "004" // Información sobre el servidor y modos

// Channel MODE
# define RPL_CHANNELMODEIS  "324" // Muestra los modos actuales del canal

// TOPIC
# define RPL_NOTOPIC        "331" // El canal no tiene topic
# define RPL_TOPIC          "332" // Topic actual del canal

// INVITE
# define RPL_INVITING       "341" // Confirmación de INVITE

// NAMES / JOIN
# define RPL_NAMREPLY       "353" // Lista de usuarios del canal
# define RPL_ENDOFNAMES     "366" // Fin de la lista de usuarios

// ====================== ERRORS ======================

// Errores generales de comandos
# define ERR_NOSUCHNICK         "401" // El nickname indicado no existe
# define ERR_NOSUCHCHANNEL      "403" // El canal indicado no existe
# define ERR_CANNOTSENDTOCHAN   "404" // No se puede enviar al canal
# define ERR_NORECIPIENT        "411" // No se ha indicado destinatario
# define ERR_NOTEXTTOSEND       "412" // No se ha indicado texto
# define ERR_UNKNOWNCOMMAND     "421" // Comando desconocido
# define ERR_NEEDMOREPARAMS     "461" // Faltan parámetros para el comando

// NICK
# define ERR_NONICKNAMEGIVEN    "431" // No se ha proporcionado nickname
# define ERR_ERRONEUSNICKNAME   "432" // Nickname inválido
# define ERR_NICKNAMEINUSE      "433" // Nickname ya está en uso
# define ERR_NICKCOLLISION      "436" // Colisión de nicknames
# define ERR_UNAVAILRESOURCE    "437" // Recurso no disponible
# define ERR_RESTRICTED         "484" // Nickname/conexión restringida

// CHANNEL / USER
# define ERR_USERNOTINCHANNEL   "441" // El usuario no está en el canal
# define ERR_NOTONCHANNEL       "442" // El cliente no está en el canal
# define ERR_USERONCHANNEL      "443" // El usuario ya está en el canal
# define ERR_NOTREGISTERED      "451" // El cliente todavía no está registrado
# define ERR_ALREADYREGISTERED  "462" // El cliente ya está registrado

// PASS / OPER
# define ERR_PASSWDMISMATCH     "464" // La contraseña no coincide
# define ERR_NOOPERHOST         "491" // El host no puede utilizar OPER

// CHANNEL MODE / JOIN
# define ERR_UNKNOWNMODE        "472" // Modo de canal desconocido
# define ERR_CHANNELISFULL      "471" // El canal está lleno
# define ERR_INVITEONLYCHAN     "473" // El canal es solo para invitados
# define ERR_BADCHANNELKEY      "475" // Contraseña del canal incorrecta
# define ERR_BADCHANMASK        "476" // Máscara/nombre de canal incorrecto
# define ERR_CHANOPRIVSNEEDED   "482" // Se necesitan privilegios de operador

#endif
