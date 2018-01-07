open BsAbstract;

module Int = {
  module Functor = Either.Functor({type t = int});
  module Apply = Either.Apply({type t = int});
  module Applicative = Either.Applicative({type t = int});
  module Monad = Either.Monad({type t = int});
  module Extend = Either.Extend({type t = int});
  module Alt = Either.Alt({type t = int});
  module Foldable = Either.Foldable({type t = int});
  module List = {
    module Traversable = Either.Traversable({type t = int}, List.Applicative);
  };
  module Array = {
    module Traversable = Either.Traversable({type t = int}, Array.Applicative);
  };
  module Option = {
    module Traversable = Either.Traversable({type t = int}, Option.Applicative);
  };
  module Bool = {
    module Eq = Either.Eq(BsAbstract.Int.Eq, BsAbstract.Bool.Eq);
    module Ord = Either.Ord(BsAbstract.Int.Ord, BsAbstract.Bool.Ord);
    module Show = Either.Show(BsAbstract.Int.Show, BsAbstract.Bool.Show);
  };
  module Float = {
    module Eq = Either.Eq(BsAbstract.Int.Eq, BsAbstract.Float.Eq);
    module Ord = Either.Ord(BsAbstract.Int.Ord, BsAbstract.Float.Ord);
    module Show = Either.Show(BsAbstract.Int.Show, BsAbstract.Float.Show);
    module Semiring = Either.Semiring({type t = int}, BsAbstract.Float.Semiring);
  };
  module String = {
    module Eq = Either.Eq(BsAbstract.Int.Eq, BsAbstract.String.Eq);
    module Ord = Either.Ord(BsAbstract.Int.Ord, BsAbstract.String.Ord);
    module Show = Either.Show(BsAbstract.Int.Show, BsAbstract.String.Show);
  };
};
module Float = {
  module Functor = Either.Functor({type t = float});
  module Apply = Either.Apply({type t = float});
  module Applicative = Either.Applicative({type t = float});
  module Monad = Either.Monad({type t = float});
  module Extend = Either.Extend({type t = float});
  module Alt = Either.Alt({type t = float});
  module Foldable = Either.Foldable({type t = float});
  module List = {
    module Traversable = Either.Traversable({type t = float}, List.Applicative);
  };
  module Array = {
    module Traversable = Either.Traversable({type t = float}, Array.Applicative);
  };
  module Option = {
    module Traversable = Either.Traversable({type t = float}, Option.Applicative);
  };
  module Bool = {
    module Eq = Either.Eq(BsAbstract.Float.Eq, BsAbstract.Bool.Eq);
    module Ord = Either.Ord(BsAbstract.Float.Ord, BsAbstract.Bool.Ord);
    module Show = Either.Show(BsAbstract.Float.Show, BsAbstract.Bool.Show);
  };
  module Int = {
    module Eq = Either.Eq(BsAbstract.Float.Eq, BsAbstract.Int.Eq);
    module Ord = Either.Ord(BsAbstract.Float.Ord, BsAbstract.Int.Ord);
    module Show = Either.Show(BsAbstract.Float.Show, BsAbstract.Int.Show);
    module Semiring = Either.Semiring({type t = float}, BsAbstract.Int.Semiring);
  };
  module String = {
    module Eq = Either.Eq(BsAbstract.Float.Eq, BsAbstract.String.Eq);
    module Ord = Either.Ord(BsAbstract.Float.Ord, BsAbstract.String.Ord);
    module Show = Either.Show(BsAbstract.Float.Show, BsAbstract.String.Show);
  };
};
module Bool = {
  module Functor = Either.Functor({type t = bool});
  module Apply = Either.Apply({type t = bool});
  module Applicative = Either.Applicative({type t = bool});
  module Monad = Either.Monad({type t = bool});
  module Extend = Either.Extend({type t = bool});
  module Alt = Either.Alt({type t = bool});
  module Foldable = Either.Foldable({type t = bool});
  module List = {
    module Traversable = Either.Traversable({type t = bool}, List.Applicative);
  };
  module Array = {
    module Traversable = Either.Traversable({type t = bool}, Array.Applicative);
  };
  module Option = {
    module Traversable = Either.Traversable({type t = bool}, Option.Applicative);
  };
  module Int = {
    module Eq = Either.Eq(BsAbstract.Bool.Eq, BsAbstract.Int.Eq);
    module Ord = Either.Ord(BsAbstract.Bool.Ord, BsAbstract.Int.Ord);
    module Show = Either.Show(BsAbstract.Bool.Show, BsAbstract.Int.Show);
    module Semiring = Either.Semiring({type t = bool}, BsAbstract.Int.Semiring);
  };
  module Float = {
    module Eq = Either.Eq(BsAbstract.Bool.Eq, BsAbstract.Float.Eq);
    module Ord = Either.Ord(BsAbstract.Bool.Ord, BsAbstract.Float.Ord);
    module Show = Either.Show(BsAbstract.Bool.Show, BsAbstract.Float.Show);
    module Semiring = Either.Semiring({type t = bool}, BsAbstract.Float.Semiring);
  };
  module String = {
    module Eq = Either.Eq(BsAbstract.Bool.Eq, BsAbstract.String.Eq);
    module Ord = Either.Ord(BsAbstract.Bool.Ord, BsAbstract.String.Ord);
    module Show = Either.Show(BsAbstract.Bool.Show, BsAbstract.String.Show);
  };
};
module String = {
  module Functor = Either.Functor({type t = string});
  module Apply = Either.Apply({type t = string});
  module Applicative = Either.Applicative({type t = string});
  module Monad = Either.Monad({type t = string});
  module Extend = Either.Extend({type t = string});
  module Alt = Either.Alt({type t = string});
  module Foldable = Either.Foldable({type t = string});
  module List = {
    module Traversable = Either.Traversable({type t = string}, List.Applicative);
  };
  module Array = {
    module Traversable = Either.Traversable({type t = string}, Array.Applicative);
  };
  module Option = {
    module Traversable = Either.Traversable({type t = string}, Option.Applicative);
  };
  module Int = {
    module Eq = Either.Eq(BsAbstract.String.Eq, BsAbstract.Int.Eq);
    module Ord = Either.Ord(BsAbstract.String.Ord, BsAbstract.Int.Ord);
    module Show = Either.Show(BsAbstract.String.Show, BsAbstract.Int.Show);
    module Semiring = Either.Semiring({type t = string}, BsAbstract.Int.Semiring);
  };
  module Float = {
    module Eq = Either.Eq(BsAbstract.String.Eq, BsAbstract.Float.Eq);
    module Ord = Either.Ord(BsAbstract.String.Ord, BsAbstract.Float.Ord);
    module Show = Either.Show(BsAbstract.String.Show, BsAbstract.Float.Show);
    module Semiring = Either.Semiring({type t = string}, BsAbstract.Float.Semiring);
  };
  module Bool = {
    module Eq = Either.Eq(BsAbstract.String.Eq, BsAbstract.Bool.Eq);
    module Ord = Either.Ord(BsAbstract.String.Ord, BsAbstract.Bool.Ord);
    module Show = Either.Show(BsAbstract.String.Show, BsAbstract.Bool.Show);
  };
};
