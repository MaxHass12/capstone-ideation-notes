require 'thread'

# Global shared resource (thread-safe with Mutex)
$balance = 0
$mutex = Mutex.new  # Mutex for thread synchronization

class PaymentJob
  def perform
    # Read the current balance (this is problematic in a multi-threaded environment)
    current_balance = $balance

    # Simulate adding 1,000,000 to the balance
    new_balance = current_balance
    1_000_000.times { new_balance += 1 }

    # Write the new balance back (race condition occurs here)
    puts "Thread #{Thread.current.object_id} writes balance: #{new_balance} (Previous global: #{$balance})"
    $balance = new_balance
  end
end

# class PaymentJob
#   def perform
#     new_balance = 0

#     # Simulate adding 1,000,000 to the balance (independent calculation)
#     1_000_000.times { new_balance += 1 }

#     # Critical Section (Protected by Mutex)
#     $mutex.synchronize do
#       puts "Thread #{Thread.current.object_id} updating balance. Previous: #{$balance}, Adding: #{new_balance}"
#       $balance += new_balance
#     end
#   end
# end

# Create 10 threads, each executing PaymentJob's perform method
threads = 10.times.map do
  Thread.new { PaymentJob.new.perform }
end

# Wait for all threads to finish execution
threads.each(&:join)

# Print the final balance
puts "Final balance: #{$balance}"  # Should be 10_000_000
