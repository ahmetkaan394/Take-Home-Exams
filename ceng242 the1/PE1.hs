module PE1 where

import Text.Printf

-- PE1: Recipe Calculator
-- The premise of this homework if to write a recipe calculator that
-- calculates: how much a recipe costs to make, what can be made with the
-- ingredients already available, and how much extra ingredients need to
-- be bought in order to make a recipe.

-- Recipe = Recipe Name [(Ingredient, Quantity)]
data Recipe = Recipe String [(String, Double)] deriving Show

-- Price = Price Ingredient Quantity Price
data Price = Price String Double Double deriving Show

-- You can use this as-is
getRounded :: Double -> Double 
getRounded x = read s :: Double
               where s = printf "%.2f" x

-- Calculate how much the given amount of the given ingredient costs

get_name::Price -> String
get_name (Price name _ _) = name
get_quantity::Price -> Double
get_quantity (Price _ quantity _) = quantity
get_price ::Price -> Double
get_price (Price _ _ price) = price

getIngredientCost :: (String, Double) -> [Price] -> Double
getIngredientCost (ing_name, the_amount) (x:xs) = if (ing_name == (get_name x)) then 
    getRounded ((the_amount*(get_price x))/(get_quantity x)) else getIngredientCost (ing_name, the_amount) xs

-- Calculate how much it costs to buy all the ingredients of a recipe
recipeCost :: Recipe -> [Price] -> Double
recipeCost (Recipe _ []) _ = 0
recipeCost (Recipe a ((ing_name,the_amount):rx)) p = (getIngredientCost (ing_name, the_amount) p) + recipeCost (Recipe a rx) p

-- Given a list of how much you already have of each ingredient,
-- calculate how much of which ingredients are missing for a recipe
difference::(String, Double) -> [(String, Double)] -> [(String, Double)]
difference (ing_name, the_amount) [] = (ing_name, the_amount):[]
difference (ing_name, the_amount) ((st_name,st_amount):stx)
    | ing_name == st_name = if (the_amount > st_amount) then (ing_name, getRounded (the_amount-st_amount)):[] else []
    | otherwise = difference (ing_name, the_amount) stx


missingIngredients :: Recipe -> [(String, Double)] -> [(String, Double)]
missingIngredients (Recipe a []) st_list = []
missingIngredients (Recipe a ((ing_name, the_amount):rx)) st_list = if ((difference (ing_name, the_amount) st_list) == []) then 
    missingIngredients (Recipe a rx) st_list else difference (ing_name,the_amount) st_list ++ missingIngredients (Recipe a rx) st_list

-- Given a list of ingredients in your kitchen, calculate what you would
-- have left after making the given recipe. If there isn't enough of an
-- ingredient, the recipe cannot be made! You shouldn't change the amount
-- of ingredient in that case.
check_it::[(String, Double)] -> (String, Double) -> Bool
check_it [] _ = False
check_it ((st_name, st_amount):stx) (ing_name, ing_amount) = if (ing_name == st_name) then True else check_it stx (ing_name, ing_amount)

check_all::[(String, Double)] -> Recipe -> Bool
check_all _ (Recipe a []) = True
check_all st_list (Recipe a ((ing_name, ing_amount):rx)) = if (check_it st_list (ing_name, ing_amount) == True) then check_all st_list (Recipe a rx) else False

isStockLess::[(String, Double)] -> (String, Double) -> Bool
isStockLess [] _ = False
isStockLess ((st_name, st_amount):stx) (ing_name, ing_amount) 
    | (ing_name == st_name) && (st_amount < ing_amount) = True
    | otherwise = isStockLess stx (ing_name, ing_amount)

isStockLess2::[(String, Double)] -> Recipe -> Bool
isStockLess2 _ (Recipe _ []) = False
isStockLess2 st_list (Recipe a ((ing_name, ing_amount):rx)) = if (not (isStockLess st_list (ing_name, ing_amount))) then isStockLess2 st_list (Recipe a rx) else True

excess:: (String, Double) -> Recipe -> [(String, Double)]
excess (st_name, st_amount) (Recipe a []) = (st_name, st_amount):[]
excess (st_name,st_amount) (Recipe a ((ing_name, the_amount):rx))
    | ing_name == st_name = (ing_name, getRounded (st_amount-the_amount)):[] 
    | otherwise = excess (st_name, st_amount) (Recipe a rx)

excess2 :: [(String, Double)] -> Recipe -> [(String, Double)]
excess2 [] _ = []
excess2 ((st_name, st_amount):stx) (Recipe a rl) = (excess (st_name, st_amount) (Recipe a rl)) ++ (excess2 stx (Recipe a rl))

makeRecipe :: [(String, Double)] -> Recipe -> [(String, Double)]
makeRecipe (st_list) (Recipe a rl) 
    | (check_all (st_list) (Recipe a rl)) && (not (isStockLess2 (st_list) (Recipe a rl))) == True = excess2 st_list (Recipe a rl)
    | otherwise  = st_list

-- Given a list of ingredients you already have, and a list of recipes,
-- make a shopping list showing how much of each ingredient you need
-- to buy, and its cost. Each ingredient mush appear in the shopping list
-- at most once (no duplicates!).
getRecipe:: Recipe -> [(String, Double)]
getRecipe (Recipe _ rl) = rl

prepareRecipe:: [Recipe] -> [(String, Double)]
prepareRecipe [] = []
prepareRecipe ((Recipe a recipe):rl) = (getRecipe (Recipe a recipe)) ++ (prepareRecipe rl)

is_in:: (String, Double) -> [(String, Double)] -> Bool
is_in _ [] = False
is_in (ing_name, ing_amount) ((ing_name2, ing_amount2):lx) = if (ing_name == ing_name2) then True else is_in (ing_name, ing_amount) lx 
design_it:: (String, Double) -> [(String, Double)] -> [(String, Double)] -> [(String, Double)]
design_it (ing_name, ing_amount) [] resulting_list =  if (is_in (ing_name, ing_amount) resulting_list) then resulting_list else (ing_name, ing_amount):[] ++ resulting_list
design_it (ing_name, ing_amount) ((ing_name2, ing_amount2):rx) resulting_list
    | (ing_name == ing_name2) = if (is_in (ing_name, ing_amount) resulting_list) then design_it (head rx) (tail rx) resulting_list else (ing_name, sum_up (ing_name, ing_amount) ((ing_name2, ing_amount2):rx)):[] ++ resulting_list
    | (not (ing_name == ing_name2)) && (is_in (ing_name, ing_amount) resulting_list) = design_it (ing_name2, ing_amount2) rx resulting_list
    | otherwise = design_it (ing_name, ing_amount) rx resulting_list

{-in_it:: (String, Double) -> [(String, Double)] -> [(String, Double)]
in_it (ing_name, ing_amount) [] = (ing_name, ing_amount):[]
in_it  (ing_name, ing_amount) ((ing_name2, ing_amount2):rx) = if (ing_name == ing_name2) then (ing_name, sum_up (ing_name, ing_amount) ((ing_name2, ing_amount2):rx)):[] else in_it (ing_name, ing_amount) rx-}

sum_up:: (String, Double) -> [(String, Double)] -> Double
sum_up (ing_name, ing_amount) [] = ing_amount
sum_up (ing_name, ing_amount) ((ing_name2, ing_amount2):rx) = if (ing_name == ing_name2) then getRounded (ing_amount + sum_up (ing_name2, ing_amount2) rx) else sum_up (ing_name, ing_amount) rx

combine:: [(String, Double)] -> [(String, Double)] -> [(String, Double)]
combine [] resulting_list = resulting_list
combine ((ing_name, ing_amount):rx) resulting_list = (combine rx (design_it (ing_name, ing_amount) rx resulting_list))

calc_prices:: [(String, Double)] -> [Price] -> [(String, Double, Double)]
calc_prices [] _ = []
calc_prices ((ing_name, ing_amount):rx) price_list = (ing_name, ing_amount, (getIngredientCost (ing_name, ing_amount) price_list)):[] ++ calc_prices rx price_list

missingIngredients2 :: [(String, Double)] -> [(String, Double)] -> [(String, Double)]
missingIngredients2 [] st_list = []
missingIngredients2 ((ing_name, the_amount):rx) st_list = if ((difference (ing_name, the_amount) st_list) == []) then 
    missingIngredients2 rx st_list else difference (ing_name,the_amount) st_list ++ missingIngredients2 rx st_list

{-my_filter:: (String, Double) -> [(String, Double)] -> [(String, Double)]
my_filter (result_name, result_amount) [] = (result_name, result_amount):[]
my_filter (result_name, result_amount) ((result2_name, result2_amount):rx) = if (result_name == result2_name) then 
    (result_name, result_amount):[] ++ (filter (\(a,b) -> a == result_name) ((result2_name, result2_amount):rx)) else 
        (result2_name, result2_amount):[] ++ (my_filter (result_name, result_amount) rx)

my_filter2:: [(String, Double)] -> [(String, Double)]
my_filter2 [] = []
my_filter2 (f:fl) = (head (my_filter f fl)) ++ my_filter2 (tail (my_filter f fl))-}

makeShoppingList :: [(String, Double)] -> [Recipe] -> [Price] -> [(String, Double, Double)]
makeShoppingList st_list recipe_list price_list = calc_prices (missingIngredients2 (combine (prepareRecipe recipe_list) []) st_list) price_list