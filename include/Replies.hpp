#ifndef REPLIES_HPP
# define REPLIES_HPP

// ==================== REPLIES ====================

// Initial client registration
# define RPL_WELCOME        001 // Client welcome
# define RPL_YOURHOST       002 // Server information
# define RPL_CREATED        003 // Server creation date
# define RPL_MYINFO         004 // Server and mode information

// Channel MODE
# define RPL_CHANNELMODEIS  324 // Displays current channel modes

// TOPIC
# define RPL_NOTOPIC        331 // Channel has no topic
# define RPL_TOPIC          332 // Current channel topic

// INVITE
# define RPL_INVITING       341 // INVITE confirmation

// NAMES / JOIN
# define RPL_NAMREPLY       353 // List of channel users
# define RPL_ENDOFNAMES     366 // End of user list

// ====================== ERRORS ======================

// General command errors
# define ERR_NOSUCHNICK         401 // The specified nickname does not exist
# define ERR_NOSUCHCHANNEL      403 // The specified channel does not exist
# define ERR_CANNOTSENDTOCHAN   404 // Cannot send to channel
# define ERR_NORECIPIENT        411 // No recipient given
# define ERR_NOTEXTTOSEND       412 // No text given
# define ERR_UNKNOWNCOMMAND     421 // Unknown command
# define ERR_NEEDMOREPARAMS     461 // Missing parameters for the command

// NICK
# define ERR_NONICKNAMEGIVEN    431 // No nickname provided
# define ERR_ERRONEUSNICKNAME   432 // Invalid nickname
# define ERR_NICKNAMEINUSE      433 // Nickname already in use
# define ERR_NICKCOLLISION      436 // Nickname collision
# define ERR_UNAVAILRESOURCE    437 // Resource unavailable
# define ERR_RESTRICTED         484 // Nickname/connection restricted

// CHANNEL / USER
# define ERR_USERNOTINCHANNEL   441 // User is not in the channel
# define ERR_NOTONCHANNEL       442 // Client is not on the channel
# define ERR_USERONCHANNEL      443 // User is already on the channel
# define ERR_NOTREGISTERED      451 // Client is not yet registered
# define ERR_ALREADYREGISTERED  462 // Client is already registered

// PASS / OPER
# define ERR_PASSWDMISMATCH     464 // Password does not match

// CHANNEL MODE / JOIN
# define ERR_UNKNOWNMODE        472 // Unknown channel mode
# define ERR_CHANNELISFULL      471 // Channel is full
# define ERR_INVITEONLYCHAN     473 // Channel is invite-only
# define ERR_BADCHANNELKEY      475 // Incorrect channel password
# define ERR_BADCHANMASK        476 // Incorrect channel mask/name
# define ERR_CHANOPRIVSNEEDED   482 // Operator privileges required

#endif
