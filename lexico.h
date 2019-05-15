void automato(char c)
{
	switch(estado)
	{
	case 0:
		if(c == '-')
		{
			estado = 14;
			tk_formado.push_back(c);
		}
		else if(ehDigito(c) != 0)
		{
			estado = 16;
			tk_formado.push_back(c);
		}
		else if(ehMaiusculoOuMinusculo(c) != 0)
		{
			estado = 1;
			tk_formado.push_back(c);
		}
		else if(c == '@')
		{
			estado = 11;
			tk_formado.push_back(c);
		}
		else if(c == '+')
		{
			estado = 19;
			tk_formado.push_back(c);
		}
		else if(c == ':' || c == '>')
		{
			estado = 21;
			tk_formado.push_back(c);
		}
		else if(c == '<')
		{
			estado = 22;
			tk_formado.push_back(c);
		}
		else if(c == '/')
		{
			estado = 23;
			tk_formado.push_back(c);
		}
		else if(c == ';' || c == '=' || c == ',')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else if(c == '.' || c == '*' || c == '(')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else if(c == ')' || c == '{' || c == '}')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 1:
		if(c == '$')
		{
			estado = 3;
			tk_formado.push_back(c);
		}
		else if(ehLetraOuDigito(c) != 0)
		{
			estado = 4;
			tk_formado.push_back(c);
		}
		else if(c == '_')
		{
			estado = 2;
			tk_formado.push_back(c);
		}
		else
		{
			if(c == '!' || c == '#' || c == '¨' || c == '&' || c == '?' || c == '°' || c == '|' || c == 'º' || c == '~' || c == '§' || c == '[' || c == ']' || c == 'ª')		
			{
				verificaEstadoToken(estado);
				erro = true;
				msg = "erro de compilacao na linha ";
			}
			else
			{
				encontrouFimToken(c);
			}
		}
		break;
	case 2:
		if(ehLetraOuDigito(c) != 0)
		{
			estado = 4;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 3:
		if(ehMinusculo(c) != 0)
		{
			estado = 4;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 4:
		if(ehLetraOuDigito(c) != 0)
		{
			estado = 4;
			tk_formado.push_back(c);
		}
		else if(c == '_')
		{
			estado = 5;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 5:
		if(ehMinusculo(c) != 0)
		{
			estado = 6;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 6:
		if(ehMinusculo(c) != 0)
		{
			estado = 7;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 7:
		if(ehMinusculo(c) != 0)
		{
			estado = 7;
			tk_formado.push_back(c);
		}
		else if(c == '_')
		{
			estado = 8;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 8:
		if(ehMinusculo(c) != 0)
		{
			estado = 9;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 9:
		if(ehMinusculo(c) != 0)
		{
			estado = 10;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 10:
		encontrouFimToken(c);
		break;
	case 11:
		if(c == '@')
		{
			estado = 12;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 12:
		if(ehLetraOuDigito(c) != 0 || ehSimboloEspecial(c) != 0 || c == ' ')
		{
			estado = 12;
		}
		else if(c == '\n')
		{
			estado = 13;
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 13:
		encontrouFimToken(c);
		countline++;
		break;
	case 14:
		if(c == '-')
		{
			estado = 15;
			tk_formado.push_back(c);
		}
		else if(ehDigito(c) != 0)
		{
			estado = 16;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 15:
		encontrouFimToken(c);
		break;
	case 16:
		if(ehDigito(c) != 0)
		{
			estado = 16;
			tk_formado.push_back(c);
		}
		else if(c == ',')
		{
			estado = 17;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 17:
		if(ehDigito(c) != 0)
		{
			estado = 18;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 18:
		if(ehDigito(c) != 0)
		{
			estado = 18;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 19:
		if(c == '+')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 20:
		if(c == '!' || c == '#' || c == '¨' || c == '&' || c == '?' || c == '°' || c == '|' || c == 'º' || c == '~' || c == '§' || c == '[' || c == ']' || c == 'ª')		
		{
			verificaEstadoToken(estado);
			erro = true;
			msg = "erro de compilacao na linha ";
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 21:
		if(c == '=')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 22:
		if(c == '>' || c == '=')
		{
			estado = 20;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 23:
		if(c == '/')
		{
			estado = 24;
			tk_formado.push_back(c);
		}
		else if(c == '#')
		{
			estado = 27;
			tk_formado.push_back(c);
		}
		else
		{
			encontrouFimToken(c);
		}
		break;
	case 24:
		if(c != '/')
		{
			estado = 24;
		}
		else if(c == '\n')
		{
			countline++;
			estado = 24;
		}
		else if(c == '/')
		{
			estado = 25;
			tk_formado.push_back(c);
		}
		else
		{
			//encontrouFimToken(c);
		}
		break;
	case 25:
		if(c != '/')
		{
			estado = 24;
			tk_formado = "//";
		}
		else if(c == '\n')
		{
			countline++;
			estado = 24;
		}
		else if(c == '/')
		{
			estado = 26;
			tk_formado.push_back(c);
		}
		else
		{
			//encontrouFimToken(c);
		}
		break;
	case 26:
		encontrouFimToken(c);
		break;
	case 27:
		if(c != '#')
		{
			estado = 27;
		}
		else if(c == '\n')
		{
			countline++;
			estado = 27;
		}
		else if(c == '#')
		{
			estado = 28;
			tk_formado.push_back(c);
		}
		else
		{
			//encontrouFimToken(c);
		}
		break;
	case 28:
		if(c != '/')
		{
			estado = 27;
			tk_formado = "/#";
		}
		else if(c == '\n')
		{
			countline++;
			estado = 27;
		}
		else if(c == '/')
		{
			estado = 26;
			tk_formado.push_back(c);
		}
		else
		{
			//encontrouFimToken(c);
		}
		break;
	default:
		//encontrouFimToken(c);
		erro = true;
		break;
	}
}
