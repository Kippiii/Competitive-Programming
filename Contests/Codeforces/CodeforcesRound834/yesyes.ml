exception Exception

let get_char n =
  match n with
  | 0 -> 'Y'
  | 1 -> 'e'
  | 2 -> 's'
  | _ -> raise Exception;;

let rec check_char n s = 
  match s with
  | c :: rest -> if c = get_char n then check_char ((n+1) mod 3) rest else false
  | [] -> true;;

let start_check s =
  match s with
  | 'Y'::rest -> check_char 1 rest
  | 'e'::rest -> check_char 2 rest
  | 's'::rest -> check_char 0 rest
  | _ -> false;;

let explode s = List.init (String.length s) (String.get s)

let bool_to_s b =
  match b with
  | true -> "YES\n"
  | false -> "NO\n"

let rec do_test_case n = 
  match n with
  | 0 -> ()
  | _ -> 
    let _ = print_string @@ bool_to_s @@ start_check @@ explode @@ read_line @@ () in
    do_test_case (n-1);;

let main () = do_test_case @@ int_of_string @@ read_line @@ ();;

main ();;