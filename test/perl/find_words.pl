#! usr/bin/perl

use strict;
print "Enter file name:"."\n";
open(FILE, <STDIN>);
#my %hash1;
my $max = 0;
while (<FILE>) {
  #chomp;
  my @line = split /\s+/, $_;
  #for (@line) {
  #  if ($_ =~ /[0-9]+/) {
  #   $hash1{$_} += 1;
  #  } 
  #}
  if ($line[2] > $max) {
    $max = $line[2];
  }
  #for my $id (keys %hash1) {
  #  print $id." ".$hash1{$id}."\n";
  #}
  
}
print "Max used memomry: ".$max."\n";
close(FILE);


