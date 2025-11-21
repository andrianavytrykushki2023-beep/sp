value_type = SAME_RULE(tokenINTEGER16);
        declaration_element = ident >> -(tokenLEFTSQUAREBRACKETS >> unsigned_value >> tokenRIGHTSQUAREBRACKETS);
        other_declaration_ident = tokenCOMMA >> declaration_element;
        declaration = value_type >> declaration_element >> *other_declaration_ident;
        index_action = tokenLEFTSQUAREBRACKETS >> expression >> tokenRIGHTSQUAREBRACKETS;
        unary_operator = SAME_RULE(tokenNOT);
        unary_operation = unary_operator >> expression;
        binary_operator = tokenAND | tokenOR | tokenEQUAL | tokenNOTEQUAL | tokenLESSOREQUAL | tokenGREATEROREQUAL | tokenPLUS | tokenMINUS | tokenMUL | tokenDIV | tokenMOD;
        binary_action = binary_operator >> expression;
        left_expression = group_expression | unary_operation | ident >> -index_action | value | cond_block__with_optionally_return_value;
        expression = left_expression >> *binary_action;
        group_expression = tokenGROUPEXPRESSIONBEGIN >> expression >> tokenGROUPEXPRESSIONEND;
        bind_left_to_right = expression >> tokenLRBIND >> ident >> -index_action;
        if_expression = SAME_RULE(expression);
        body_for_true__with_optionally_return_value = SAME_RULE(block_statements__with_optionally_return_value);
        false_cond_block_without_else__with_optionally_return_value = tokenELSE >> tokenIF >> if_expression >> body_for_true__with_optionally_return_value;
        body_for_false__with_optionally_return_value = tokenELSE >> block_statements__with_optionally_return_value;
        cond_block__with_optionally_return_value = tokenIF >> if_expression >> body_for_true__with_optionally_return_value >> *false_cond_block_without_else__with_optionally_return_value >> -body_for_false__with_optionally_return_value;
        cond_block__with_optionally_return_value_and_optionally_bind = cond_block__with_optionally_return_value >> -(tokenLRBIND >> ident >> -index_action);
        cycle_begin_expression = SAME_RULE(expression);
        cycle_end_expression = SAME_RULE(expression);
        cycle_counter = SAME_RULE(ident);
        cycle_counter_lr_init = cycle_begin_expression >> tokenLRBIND >> cycle_counter;
        cycle_counter_init = SAME_RULE(cycle_counter_lr_init);
        cycle_counter_last_value = SAME_RULE(cycle_end_expression);
        cycle_body = tokenDO >> (statement | block_statements);
        forto_cycle = tokenFOR >> cycle_counter_init >> tokenTO >> cycle_counter_last_value >> cycle_body;
        input = tokenGET >> (ident >> -index_action | tokenGROUPEXPRESSIONBEGIN >> ident >> -index_action >> tokenGROUPEXPRESSIONEND);
        output = tokenPUT >> expression;
        statement = bind_left_to_right | cond_block__with_optionally_return_value_and_optionally_bind | forto_cycle | input | output | tokenSEMICOLON;
        block_statements = tokenBEGINBLOCK >> *statement >> tokenENDBLOCK;
        block_statements__with_optionally_return_value = tokenBEGINBLOCK >> *statement >> -expression >> tokenENDBLOCK;
        program = BOUNDARIES >> tokenNAME >> program_name >> tokenSEMICOLON >> tokenDATA >> (-declaration) >> tokenSEMICOLON >> tokenBEGIN >> *statement >> tokenEND;
        digit = digit_0 | digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        non_zero_digit = digit_1 | digit_2 | digit_3 | digit_4 | digit_5 | digit_6 | digit_7 | digit_8 | digit_9;
        unsigned_value = ((non_zero_digit >> *digit) | digit_0) >> BOUNDARIES;
        value = -sign >> unsigned_value >> BOUNDARIES;
        letter_in_upper_case = A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z;
        ident = tokenUNDERSCORE >> letter_in_upper_case >> STRICT_BOUNDARIES;
        sign = sign_plus | sign_minus;
        sign_plus = SAME_RULE(tokenPLUS);
        sign_minus = SAME_RULE(tokenMINUS);
        digit_0 = '0';
        digit_1 = '1';
        digit_2 = '2';
        digit_3 = '3';
        digit_4 = '4';
        digit_5 = '5';
        digit_6 = '6';
        digit_7 = '7';
        digit_8 = '8';
        digit_9 = '9';
tokenINTEGER16 = "Int16" >> STRICT_BOUNDARIES;
        tokenCOMMA = "," >> BOUNDARIES;
        tokenNOT = "!" >> STRICT_BOUNDARIES;
        tokenAND = "And" >> STRICT_BOUNDARIES;
        tokenOR = "Or" >> STRICT_BOUNDARIES;
        tokenEQUAL = "Eg" >> STRICT_BOUNDARIES;
        tokenNOTEQUAL = "Ne" >> STRICT_BOUNDARIES;
        tokenLESSOREQUAL = "<<" >> STRICT_BOUNDARIES;
        tokenGREATEROREQUAL = ">>" >> STRICT_BOUNDARIES;
        tokenPLUS = "+" >> BOUNDARIES;
        tokenMINUS = "-" >> BOUNDARIES;
        tokenMUL = "Mul" >> STRICT_BOUNDARIES;
        tokenDIV = "Div" >> STRICT_BOUNDARIES;
        tokenMOD = "Mod" >> STRICT_BOUNDARIES;
        tokenGROUPEXPRESSIONBEGIN = "(" >> BOUNDARIES;
        tokenGROUPEXPRESSIONEND = ")" >> BOUNDARIES;
        tokenLRBIND = "->" >> BOUNDARIES;
        tokenELSE = "Else" >> STRICT_BOUNDARIES;
        tokenIF = "If" >> STRICT_BOUNDARIES;
        tokenDO = "Do" >> STRICT_BOUNDARIES;
        tokenFOR = "For" >> STRICT_BOUNDARIES;
        tokenTO = "To" >> STRICT_BOUNDARIES;
        tokenGET = "Get" >> STRICT_BOUNDARIES;
        tokenPUT = "Put" >> STRICT_BOUNDARIES;
        tokenNAME = "Program" >> STRICT_BOUNDARIES;
        tokenDATA = "Var" >> STRICT_BOUNDARIES;
        tokenBEGIN = "Begin" >> STRICT_BOUNDARIES;
        tokenEND = "End" >> STRICT_BOUNDARIES;
        tokenBEGINBLOCK = "{" >> BOUNDARIES;
        tokenENDBLOCK = "}" >> BOUNDARIES;
        tokenLEFTSQUAREBRACKETS = "[" >> BOUNDARIES;
        tokenRIGHTSQUAREBRACKETS = "]" >> BOUNDARIES;
        tokenSEMICOLON = ";" >> BOUNDARIES;
        STRICT_BOUNDARIES = (BOUNDARY >> *(BOUNDARY)) | (!(qi::alpha | qi::char_("_")));
        BOUNDARIES = (BOUNDARY >> *(BOUNDARY) | NO_BOUNDARY);
        BOUNDARY = BOUNDARY_SPACE | BOUNDARY_TAB | BOUNDARY_CARRIAGE_RETURN | BOUNDARY_LINE_FEED | BOUNDARY_NULL;
        BOUNDARY_SPACE = " ";
        BOUNDARY_TAB = "\t";
        BOUNDARY_CARRIAGE_RETURN = "\r";
        BOUNDARY_LINE_FEED = "\n";
        BOUNDARY_NULL = "\0";
        NO_BOUNDARY = "";
        tokenUNDERSCORE = "_";
        A = "A";
        B = "B";
        C = "C";
        D = "D";
        E = "E";
        F = "F";
        G = "G";
        H = "H";
        I = "I";
        J = "J";
        K = "K";
        L = "L";
        M = "M";
        N = "N";
        O = "O";
        P = "P";
        Q = "Q";
        R = "R";
        S = "S";
        T = "T";
        U = "U";
        V = "V";
        W = "W";
        X = "X";
        Y = "Y";
        Z = "Z";



    }
    std::ostringstream& error_stream_;
qi::rule<Iterator>
        program_name,
        value_type,
        declaration_element,
        other_declaration_ident,
        declaration,
        index_action,
        unary_operator,
        unary_operation,
        binary_operator,
        binary_action,
        left_expression,
        expression,
        group_expression,
        bind_left_to_right,
        if_expression,
        body_for_true__with_optionally_return_value,
        false_cond_block_without_else__with_optionally_return_value,
        body_for_false__with_optionally_return_value,
        cond_block__with_optionally_return_value,
        cond_block__with_optionally_return_value_and_optionally_bind,
        cycle_begin_expression,
        cycle_end_expression,
        cycle_counter,
        cycle_counter_lr_init,
        cycle_counter_init,
        cycle_counter_last_value,
        cycle_body,
        forto_cycle,
        input,
        output,
        statement,
        block_statements,
        block_statements__with_optionally_return_value,
        program,
        tokenINTEGER16, tokenCOMMA, tokenNOT, tokenAND, tokenOR, tokenEQUAL, tokenNOTEQUAL,
        tokenLESSOREQUAL, tokenGREATEROREQUAL, tokenLT, tokenGT,
        tokenPLUS, tokenMINUS, tokenMUL, tokenDIV, tokenMOD,
        tokenGROUPEXPRESSIONBEGIN, tokenGROUPEXPRESSIONEND,
        tokenLRBIND,
        tokenELSE, tokenIF, tokenDO, tokenFOR, tokenTO,
        tokenGET, tokenPUT, tokenNAME, tokenDATA,
        tokenBEGIN, tokenEND, tokenBEGINBLOCK, tokenENDBLOCK,
        tokenLEFTSQUAREBRACKETS, tokenRIGHTSQUAREBRACKETS, tokenSEMICOLON,
        STRICT_BOUNDARIES, BOUNDARIES, BOUNDARY,
        BOUNDARY_SPACE, BOUNDARY_TAB, BOUNDARY_CARRIAGE_RETURN, BOUNDARY_LINE_FEED, BOUNDARY_NULL,
        NO_BOUNDARY,
        sign, sign_plus, sign_minus,
        digit_0, digit_1, digit_2, digit_3, digit_4, digit_5, digit_6, digit_7, digit_8, digit_9,
        digit, non_zero_digit, value, unsigned_value,
        letter_in_upper_case,
        ident,
        tokenUNDERSCORE,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
};
   


int main(int argc, char* argv[]) {
    char* text_;
    char fileName[128] = DEFAULT_INPUT_FILE;
    char choice[2] = { fileName[0], fileName[1] };
    system("CLS");
    std::cout << "Enter file name(Enter \"" << choice[0] << "\" to use default \"" DEFAULT_INPUT_FILE "\"):";
    std::cin >> fileName;
    if (fileName[0] == choice[0] && fileName[1] == '\0') {
        fileName[1] = choice[1];
    }
    size_t sourceSize = loadSource(&text_, fileName);
    if (!sourceSize) {
#ifdef RERUN_MODE
        (void)getchar();
        printf("\nEnter 'y' to rerun program action(to pass action enter other key): ");
        char valueByGetChar = getchar();
        if (valueByGetChar == 'y' || valueByGetChar == 'Y') {
            system((std::string("\"") + argv[0] + "\"").c_str());
        }
        return 0;
