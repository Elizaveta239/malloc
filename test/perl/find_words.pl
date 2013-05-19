#! usr/bin/perl

use strict;
print "Enter file name:"."\n";
open(FILE, <STDIN>);
my %hash1;
while (<FILE>) {
  chomp;
  my @line = split /\s+/, $_;
  for (@line) {
    if ($_ =~ /[A-Z]+[a-zA-Z]*/) {
      $hash1{$_} += 1;
    } 
  }
  for my $id (keys %hash1) {
    print $id." ".$hash1{$id}."\n";
  }
}
close(FILE);


